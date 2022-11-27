// Adaptive integration with Simpson's Rules
// The adaptive mechanism is introduced by Romberg

#include <math.h>
#include <iostream>
#include <vector>

class function {
    public:
        virtual double operator() (double x) = 0;
};

struct Value {
    double a;
    double f_a;
    double f_c;
    double f_b;
    double h;
    double Tol;
    double S_a_b;
};

class Simpson {
    public:
        Simpson(function & f_): f(f_) {}
        Value eval(double a, double b, double f_a, double f_b, double tol) {
            Value _val;
            _val.a = a;
            _val.Tol = tol;
            _val.h = (b - a) / 2;
            _val.f_a = f_a;
            _val.f_c = f(a + _val.h);
            _val.f_b = f_b;
            _val.S_a_b = (_val.f_a + 4 * _val.f_c + _val.f_b) * _val.h / 3;
            return _val;
        }
        double f_call(double x) {
            return f(x);
        }
    private:
        function& f;
};

class Romberg {
    public:
        Romberg(Simpson & simpson_): simpson(simpson_) {}
        double eval(double a, double b, double tol) {
            // num is the time of calling trapezoidal method, with sub-divided interval
            // inspired by 4.5 Adaptive Integration of the textbook "Applied Numerical Analysis"
            std::vector<Value> stack;
            stack.push_back(simpson.eval(a, b, simpson.f_call(a), simpson.f_call(b), tol));
            double total = 0;
            while (stack.size() > 0) {
                Value val = stack.back();
                stack.pop_back();
                Value val_1 = simpson.eval(val.a, val.a + val.h, val.f_a, val.f_c, val.Tol / 2);
                Value val_2 = simpson.eval(val.a + val.h, val.a + 2 * val.h, val.f_c, val.f_b, val.Tol / 2);
                if (abs(val.S_a_b - val_1.S_a_b - val_2.S_a_b) < val.Tol) {
                    double more_acurate = val_1.S_a_b + val_2.S_a_b;
                    total += more_acurate + (more_acurate - val.S_a_b) / 15;
                } else {
                    stack.push_back(val_1);
                    stack.push_back(val_2);
                }
            }
            return total;
        }
    private:
        Simpson& simpson;
};

class test_func : public function {
    public:
        double operator() (double x) {
            std::cout << "call" << std::endl;
            return 1 / (x * x);
        }
};

int main() {
    double a = 0.2, b = 1.0, tol = 0.02;
    test_func _test_func;
    Simpson _simpson(_test_func);
    double h = (b - a) / 2;
    int num = 4;
    Romberg _romberg(_simpson);
    double val_1 = _romberg.eval(a, b, tol);
    std::cout << val_1 << std::endl;
}


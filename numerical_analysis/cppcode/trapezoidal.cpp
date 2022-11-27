#include <math.h>
#include <iostream>

class function {
    public:
        virtual double operator() (double x) = 0;
};

class Trapezoidal {
    public:
        Trapezoidal(function & f_): f(f_) {}
        double eval(double a, double b, double h) {
            double value = f(a);
            double c = a + h;
            double _b = b - c / 10;
            while (c < _b) {
                value += 2 * f(c);
                c += h;
            }
            value += f(c);
            value *= h / 2;
            return value;
        }
    private:
        function& f;
};

class Romberg {
    public:
        Romberg(Trapezoidal & trapezoidal_): trapezoidal(trapezoidal_) {}
        double eval(double a, double b, double h, int num) {
            // num is the time of calling trapezoidal method, with sub-divided interval
            double* _list = new double[num];
            for (int i = 0; i < num; i++) {
                _list[i] = trapezoidal.eval(a, b, h);
                h /= 2;
            }
            int num_ = num - 1;
            int order = 4;
            while (num_ > 0) {
                for (int i = 0; i < num_; i++) {
                    _list[i] = _list[i + 1] + (_list[i + 1] - _list[i]) / (order - 1);                    
                }
                order *= 4;
                num_ -= 1;
            }
            double value = _list[0];
            delete _list;
            return value;
        }
    private:
        Trapezoidal& trapezoidal;
};

class test_func : public function {
    public:
        double operator() (double x) {
            return exp(-x*x);
        }
};

int main() {
    double a = 0.2, b = 1.5;
    test_func _test_func;
    Trapezoidal _trapezoidal(_test_func);
    double h = (b - a) / 2;
    int num = 4;
    double val_1 = _trapezoidal.eval(a, b, h / pow(2, num - 1));
    Romberg _romberg(_trapezoidal);
    double val_2 = _romberg.eval(a, b, h, num);
    std::cout << val_1 << std::endl;
    std::cout << val_2; // val_2 is more accurate than val_1
    // more accurate: 0.65882336
}

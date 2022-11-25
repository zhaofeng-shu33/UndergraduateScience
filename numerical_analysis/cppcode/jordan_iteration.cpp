#include "base.h"

int main() {
    int n = 3;
    double p[] = {6, -2, 1,
        -2, 7, 2,
        1, 2, -5};
    double q[] = {11, 5, -1};
     
    Linear_Equation my_linear_equation(n); //construct an equation with n variables
    my_linear_equation.Set_Matrix(p);
    my_linear_equation.Set_Linear_Equation(q); 
 
     //my_linear_equation.Print_Linear_Equation();
    my_linear_equation.Solve_Iterate(100);
    
    cout << "solution vector is \n";
    my_linear_equation.show_solution();
     
    return 0;
}



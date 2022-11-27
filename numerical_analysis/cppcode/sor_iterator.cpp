#include "base.h"

int main() {
    int n = 3;
    double p[] = {4, 3, 0,
        3, 4, -1,
        0, -1, 4};
    double q[] = {24, 30, -24};
     
    Linear_Equation my_linear_equation(n); //construct an equation with n variables
    my_linear_equation.Set_Matrix(p);
    my_linear_equation.Set_Linear_Equation(q); 
 
     //my_linear_equation.Print_Linear_Equation();
    double initial_solution_vector[] = {1, 1, 1};
    double true_solution_vector[] = {3, 4, -5};
    my_linear_equation.Solve_Iterate_SOR(1.25, 16, initial_solution_vector, true_solution_vector);
    
    cout << "solution vector is \n";
    my_linear_equation.show_solution();
     
    return 0;
}



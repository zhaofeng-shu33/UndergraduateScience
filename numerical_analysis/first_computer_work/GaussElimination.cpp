#include "base.h"

int main() {
    char ch1;
    cout << "input the type (R or S), R is regular matrix while S represents sparse matrix\n";
    cin >> ch1;
    if (ch1 != 'S' && ch1 != 'R') {
        cout << "invalid type \n";
        exit(0); 
    }
    int n;
    cout << "input the dimension\n";
    cin >> n;
    double* p = new double[n*n];
    cout << "input the matrix \n";
    if(ch1=='R'){
        for(int i=0;i<n;i++)
          for(int j=0;j<n;j++)
              cin>>p[i*n+j];
    }
    if(ch1=='S'){
        int K;
        cin>>K;
        for(int i=0;i<n;i++)
          for(int j=0;j<n;j++)
              p[i*n+j]=0;

        for(int r=0;r<K;r++){
         int i2,j2,data;
         cin>>i2>>j2>>data;
         p[(i2-1)*n+j2-1]=data; 
        }  
   
    }
    cout << "input the b vector \n";
      double* q=new double[n];
        for(int i=0;i<n;i++)
              cin>>q[i];   
     
    Linear_Equation my_linear_equation(n); //construct an equation with n variables
    my_linear_equation.Set_Matrix(p);
    my_linear_equation.Set_Linear_Equation(q); 
 
     //my_linear_equation.Print_Linear_Equation();
    my_linear_equation.Solve();
    
    cout << "solution vector is \n";
    my_linear_equation.show_solution();
    delete [] p;
    delete [] q;
     
    return 0;
}



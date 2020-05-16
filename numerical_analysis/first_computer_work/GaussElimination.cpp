#include<iostream>
#include<fstream>
#include <cstring>
#include<cmath>
using namespace std;
ofstream fout("GaussElimination1.txt");

void swap(double* a,double* b){
  double t=*a;
  *a=*b;
  *b=t;
}
class Matrix{
  public:
    Matrix(int a){
      order=a;
      initial_address=new double[order*order];
    }
    ~Matrix(){}
    void Set_Matrix(double* p){
      for(int i=0;i<order*order;i++){
          initial_address[i]=p[i];
      }  
    }
  public:
    int order;
    double* initial_address;
};  
class Linear_Equation: public Matrix{
  public:
    Linear_Equation(int a):Matrix(a){ 
      b=new double[a];
      solution_vector=new double[a];
      ERROR=0;
    }
    ~Linear_Equation(){}
    void Set_Linear_Equation(double* a){
        for(int i=0;i<order;i++)
            b[i]=a[i];
     
    }
    void Print_Linear_Equation(){
         for(int i=0;i<order;i++){
           for(int j=0;j<order;j++)
              cout<<initial_address[i*order+j]<<'\t';
          cout<<b[i]; 
          cout<<endl;
         }
    } 
    void Solve();
    void show_solution(){
         if(ERROR){cout<<0<<endl;return;}
         for(int i=0;i<order;i++)
             cout<<solution_vector[i]<<' ';
         cout<<endl;
    }      
  private: 
    double* solution_vector,*b;
    bool ERROR;
};  
int main(){
    char ch1;
    cout << "input the type (R or S)\n";
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
void Linear_Equation::Solve(){
   Matrix Left(order);double Permu[order]; 
   for(int i=0;i<order;i++)
       Permu[i]=i;
    for(int k = 0; k <= order - 2; k++ ){ //从矩阵第一行到第order-1行进行 高斯消去
        double max1=initial_address[k*order+k];int row=k;
        for(int i = k; i < order; i++ ){
            if(abs(initial_address[i*order+k])>abs(max1)){
                 max1=initial_address[i*order+k];
                 row=i;
               }
        }
           
        if(row!=k){
           for(int j=k; j<order; j++)
             swap(initial_address+k*order+j,initial_address+row*order+j);
           swap(b+k,b+row);
        }
       swap(Permu+k,Permu+row);
      //上面的算法使用选主元的Gauss 消去法使得a[k][k]为所在列绝对值最大的元素。
      //同时记下每步使用的初等排列阵。  
      
     double l[order];
     for(int i = k+1; i < order; i++ ){
       
         l[i]=initial_address[i*order+k]/initial_address[k*order+k];
         Left.initial_address[i*order+k]=l[i];
         b[i]-=l[i]*b[k];
          for(int j=k+1; j< order; j++ ){
              initial_address[i*order+j]-=l[i]*initial_address[k*order+j];
              

          }  
     }
          //用数组l对Left矩阵进行赋值。
      
       
  }  
  //上面的代码将矩阵化为上三角阵U，但需注意上三角阵主对角元没有归一化 
    if(fabs(initial_address[order*order-1])<0.001){ERROR=1;return;} 
  solution_vector[order-1]=b[order-1]/initial_address[order*order-1]; //从最后一行开始求解。 
  for(int i=order-2; i>=0; i--){
      double tem=0;
      for(int j=i+1;j<order;j++)
          tem+=initial_address[i*order+j]*solution_vector[j]; 
      
      if(fabs(initial_address[i*order+i])<0.001){ERROR=1;return;} 
      solution_vector[i]=(b[i]-tem)/initial_address[i*order+i];//cout<<solution_vector[i]<<endl;
  }
}  

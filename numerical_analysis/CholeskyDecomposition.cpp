#include<iostream>
#include<fstream>
#include <cstring>
#include<cmath>
using namespace std;
ofstream fout("answerOfExperimentProblem.txt");

void swap(double* a,double* b){
  double t=*a;
  *a=*b;
  *b=t;
 // cout<<*a<<' '<<*b<<endl;
}
bool is_solution(double *a,double* b,int index){
   for(int i=0;i<index;i++){
       double tem=0;
       for(int j=0;j<index;j++)
          tem+=a[i*index+j]*b[j];
       if(fabs(tem-b[i])>0.1){
         cout<<i<<' '<<tem<<' '<<b[i]<<endl;
       return false;
       }  
 }

 return true;
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
    void Print_Matrix(){
      for(int i=0;i<order;i++){
          for(int j=0;j<order;j++)
              cout<<initial_address[i*order+j]<<'\t';
          cout<<endl;
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
    void Solve2();
    void show_solution(){
         fout<<"The order is "<<order<<endl;
         for(int i=0;i<order;i++)
             fout<<solution_vector[i]<<endl;
    }      
  private: 
    double* solution_vector,*b;
};  
int main(){
  for(int n=2;n<=20;n++){
  double* p=new double[n*n];
  for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
         p[i*n+j]=1.0/(i+j+1);
  double* q=new double[n];
  for(int i=0;i<n;i++){
      q[i]=0;
      for(int j=0;j<n;j++)
          q[i]+=p[i*n+j];
  }
  Linear_Equation my_linear_equation(n);
  my_linear_equation.Set_Matrix(p);
  my_linear_equation.Set_Linear_Equation(q); 
 
  // my_linear_equation.Print_Linear_Equation();
  my_linear_equation.Solve();
  my_linear_equation.show_solution();
  delete [] p;
  delete [] q;
  }  
  fout.close();  
  char ch;
  cin>>ch;
  return 0;
}    
void Linear_Equation::Solve(){
   Matrix Left(order); 
    for(int k = 0; k <order; k++ ){
        for(int j=k;j<order;j++){
           double tem=0;
           for(int r=0;r<k;r++){
              tem+=Left.initial_address[j*order+r]*Left.initial_address[k*order+r];
           }  
         if(j==k){
              Left.initial_address[k*order+k]=sqrt(initial_address[k*order+k]-tem);
         }  
         else{      
             Left.initial_address[j*order+k]=(initial_address[j*order+k]-tem)/Left.initial_address[k*order+k];
         }  
        }  
    }  
      
  for(int i=0;i<order;i++){
      for(int j=i+1;j<order;j++){
          Left.initial_address[i*order+j]=0;
      }  
  }
  cout<<endl;
       
       
       
       
     
  //上面的代码完成矩阵的Cholesky分解。 
  double Intermediate[order];
  for(int i=0;i<order;i++){
      double tem=0;
      for(int r=0;r<i;r++)
          tem+= Left.initial_address[i*order+r]*Intermediate[r];
      Intermediate[i]=(b[i]-tem)/Left.initial_address[i*order+i];
  }
  /*cout<<"Intermediate Solution:\n";  
  for(int i=0;i<order;i++)
      cout<<Intermediate[i]<<endl;
   */
  for(int i=order-1; i>=0; i--){
      double tem=0;
      for(int r=i+1;r<order;r++)
          tem+=Left.initial_address[r*order+i]*solution_vector[r]; 
      
      solution_vector[i]=(Intermediate[i]-tem)/Left.initial_address[i*order+i];
  }      
  //上面的代码分两步求解L*Transpose(L)x=b. 
  
  
  /*for(int i=0;i<order;i++){
           for(int j=0;j<order;j++)
              cout<<Left.initial_address[i*order+j]<<'\t';
  cout<<endl;
  }//打印下三角阵L 
  cout<<endl;
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++)
              cout<<Left.initial_address[j*order+i]<<'\t';
  cout<<endl;
  }//打印上三角阵Transpose(L)
   */
}
void Linear_Equation::Solve2(){//加边的Cholesky Decomposition. 
   Matrix Left(order);
    Left.initial_address[0]=sqrt(initial_address[0]);
    for(int i = 1; i <order; i++ ){
        double* c=new double[i];
        double* Intermediate=new double[i];
        for(int j=0;j<i;j++)
            c[j]=initial_address[i*order+j];
       
        
          for(int t=0;t<i;t++){
                double tem=0;
             for(int r=0;r<t;r++)
            tem+= Left.initial_address[t*order+r]*Intermediate[r];
            Intermediate[t]=(c[t]-tem)/Left.initial_address[t*order+t];
          }
         
        double tem=0;  
        for(int t=0;t<i;t++){
            tem+=Intermediate[t]*Intermediate[t];
            Left.initial_address[i*order+t]=Intermediate[t];
        }  
        Left.initial_address[i*order+i]=sqrt(initial_address[i*order+i]-tem);
        delete [] c;
        delete [] Intermediate;    
       
    }     
  //上面的代码完成矩阵的Cholesky分解。 
  double Intermediate[order];
  for(int i=0;i<order;i++){
      double tem=0;
      for(int r=0;r<i;r++)
          tem+= Left.initial_address[i*order+r]*Intermediate[r];
      Intermediate[i]=(b[i]-tem)/Left.initial_address[i*order+i];
  }
  cout<<"Intermediate Solution:\n";  
  for(int i=0;i<order;i++)
      cout<<Intermediate[i]<<endl;
   
  for(int i=order-1; i>=0; i--){
      double tem=0;
      for(int r=i+1;r<order;r++)
          tem+=Left.initial_address[r*order+i]*solution_vector[r]; 
      
      solution_vector[i]=(Intermediate[i]-tem)/Left.initial_address[i*order+i];
  }      
  //上面的代码分两步求解L*Transpose(L)x=b. 
  
  
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++)
              cout<<Left.initial_address[i*order+j]<<'\t';
  cout<<endl;
  }//打印下三角阵L 
  cout<<endl;
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++)
              cout<<Left.initial_address[j*order+i]<<'\t';
  cout<<endl;
  }//打印上三角阵Transpose(L)
   
}  

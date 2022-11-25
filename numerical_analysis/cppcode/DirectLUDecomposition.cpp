#include<iostream>
#include<fstream>
#include <cstring>
#include<cmath>
using namespace std;
//ofstream fout("answerOfExperimentProblem.txt");

void swap(double* a,double* b){
  double t=*a;
  *a=*b;
  *b=t;
 // cout<<*a<<' '<<*b<<endl;
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
        for(int i=0;i<order;i++){
            b[i]=a[i];
            solution_vector[i]=0;
        }  
     
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
         cout<<"The order is "<<order<<endl;
         for(int i=0;i<order;i++)
             cout<<solution_vector[i]<<endl;
    }      
  private: 
    double* solution_vector,*b;
};  
int main(){
  
  double p[9]={4,-1,1,-1,4.25,2.75,1,2.75,3.5};
  double q[3]={6,-0.5,1.25};
  Linear_Equation my_linear_equation(3);
  my_linear_equation.Set_Matrix(p);
  my_linear_equation.Set_Linear_Equation(q); 
 
  my_linear_equation.Print_Linear_Equation();
  my_linear_equation.Solve();
  my_linear_equation.show_solution();
   
 
  char ch;
  cin>>ch;
  return 0;
}    
void Linear_Equation::Solve(){
  
  double Left[order*order],Upper[order*order]; 
    for(int k = 0; k <order; k++ ){ 
       for(int j=k;j<order;j++){
           double tem=0;
           for(int r=0;r<k;r++)
               tem+=Left[k*order+r]*Upper[r*order+j];
               
       Upper[k*order+j]=initial_address[k*order+j]-tem;
       }  
      
       for(int i=k+1;i<order;i++){
           double tem=0;
           for(int r=0;r<k;r++)
               tem+=Left[i*order+r]*Upper[r*order+k];
       Left[i*order+k]=(initial_address[i*order+k]-tem)/Upper[k*order+k];
       }
    }    
  for(int i=0;i<order;i++){
      Left[i*order+i]=1;
      for(int j=i+1;j<order;j++){
          Left[i*order+j]=0;
          Upper[j*order+i]=0;
      }  
  }
       
       
       
     
  //上面的代码完成矩阵的LU分解。 
  double Intermediate[order];
  
  for(int i=0;i<order;i++){
      double tem=0;
      for(int w=0;w<i;w++)
          tem+= Left[i*order+w]*Intermediate[w];
      Intermediate[i]=b[i]-tem;
  }
  cout<<"Intermediate Solution:\n";  
  for(int i=0;i<order;i++)
      cout<<Intermediate[i]<<endl;
  for(int i=order-1; i>=0; i--){
      double tem=0;
      for(int w=i+1;w<order;w++)
          tem+=Upper[i*order+w]*solution_vector[w]; 
      
      solution_vector[i]=(Intermediate[i]-tem)/Upper[i*order+i];
  }      
     
  //上面的代码分两步求解LUx=b. 
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++)
              cout<<Left[i*order+j]<<'\t';
  cout<<endl;
  }//打印下三角阵L 
  cout<<endl;
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++)
              cout<<Upper[i*order+j]<<'\t';
  cout<<endl;
  }//打印上三角阵L 
}  

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
         cout<<"The order is "<<order<<endl;
         for(int i=0;i<order;i++)
             cout<<solution_vector[i]<<endl;
    }      
  private: 
    double* solution_vector,*b;
};  
int main(){
  //例子见课本P55例题 
  const int order=5;
  double p[order*order]={2,-1,0,0,1,-1,2,-1,0,0,0,-1,2,-1,0,0,0,-1,2,-1,1,0,0,-1,2};
  double q[order]={1,0,0,0,0};
  Linear_Equation my_linear_equation(order);
  my_linear_equation.Set_Matrix(p);
  my_linear_equation.Set_Linear_Equation(q);
  my_linear_equation.Print_Linear_Equation();
  my_linear_equation.Solve2();
  my_linear_equation.show_solution();
  char ch;
  cin>>ch;
  return 0;
}    
void Linear_Equation::Solve(){//追赶法，见课本P53 
   double Lower[order],Upper[order];
   Upper[0]=initial_address[0];
   for(int i=1;i<order;i++){
       Lower[i]=initial_address[i*order+i-1]/Upper[i-1];
       Upper[i]=initial_address[i*order+i]-Lower[i]*initial_address[(i-1)*order+i];
   }
   //计算出L和U的全部元素  
   double Intermediate[order];
   Intermediate[0]=b[0];
   for(int i=1;i<order;i++)
       Intermediate[i]=b[i]-Lower[i]*Intermediate[i-1];
   solution_vector[order-1]=Intermediate[order-1]/Upper[order-1];
   for(int i=order-2;i>=0;i--)
       solution_vector[i]=(Intermediate[i]-initial_address[i*order+i+1]*solution_vector[i+1])/Upper[i];
  //上面的代码分两步求解LUx=b. 
  
  cout<<endl;
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++){
               if(i==j)
                  cout<<1<<'\t';
               else if(i==j+1)
                  cout<<Lower[i]<<'\t';
               else
                  cout<<0<<'\t';
           }  
  cout<<endl;
  }//打印下三角阵L 
  cout<<endl;
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++){
               if(i==j)
                  cout<<Upper[i]<<'\t';
               else if(j==i+1)
                  cout<<initial_address[i*order+j]<<'\t';
               else
                  cout<<0<<'\t';
           }  
   cout<<endl;
  }//打印上三角阵Transpose(L)
  cout<<endl; 
} 
void Linear_Equation::Solve2(){//to solve cyclic tridiagonal equation
   double Lower[order-1],Upper[order];
   Upper[0]=initial_address[0];
   for(int i=1;i<order-1;i++){
       Lower[i]=initial_address[i*order+i-1]/Upper[i-1];
       Upper[i]=initial_address[i*order+i]-Lower[i]*initial_address[(i-1)*order+i];
   }
   //计算出L'和U'的全部元素  
   double Intermediate1[order-1],Intermediate2[order-1];
   Intermediate1[0]=initial_address[order-1];
   for(int i=1;i<order-1;i++)
       Intermediate1[i]=-Lower[i]*Intermediate1[i-1];
   Intermediate1[order-2]+=initial_address[(order-1)*order-1];
   
   Intermediate2[0]=initial_address[order-1]/Upper[0];
 //  cout<<"Test1: "<<Intermediate2[order-2]<<' '<<initial_address[order*order-2]<<' '<<Upper[order-2]<<endl;
   for(int i=1;i<order-1;i++)
       Intermediate2[i]=-Intermediate2[i-1]*initial_address[(i-1)*order+i]/Upper[i];
   Intermediate2[order-2]+=initial_address[order*order-2]/Upper[order-2];
   
   double tem=0;
   for(int i=0;i<order-1;i++)
       tem+=Intermediate1[i]*Intermediate2[i];
   Upper[order-1]=initial_address[order*order-1]-tem;
   
   double Intermediate[order];
   Intermediate[0]=b[0];
   for(int i=1;i<order-1;i++)
       Intermediate[i]=b[i]-Lower[i]*Intermediate[i-1];
   Intermediate[order-1]=b[order-1];
   for(int i=0;i<order-1;i++)
       Intermediate[order-1]-=Intermediate2[i]*Intermediate[i];
 
   solution_vector[order-1]=Intermediate[order-1]/Upper[order-1];
   solution_vector[order-2]=(Intermediate[order-2]-solution_vector[order-1]*Intermediate1[order-2])/Upper[order-2];
   for(int i=order-3;i>=0;i--)
       solution_vector[i]=(Intermediate[i]-initial_address[i*order+i+1]*solution_vector[i+1]-solution_vector[order-1]*Intermediate1[i])/Upper[i];
  //上面的代码分两步求解LUx=b. 
  
  cout<<endl;
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++){
               if(i==j)
                  cout<<Upper[i]<<'\t';
               else if(j==i+1&&j!=order-1)
                  cout<<initial_address[i*order+j]<<'\t';
               else if(j==order-1&&j!=i)
                  cout<<Intermediate1[i]<<'\t';
               else
                  cout<<0<<'\t';
           }  
  cout<<endl;
  }//打印上三角阵U 
  cout<<endl;
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++){
               if(i==j)
                  cout<<1<<'\t';
               else if(i==j+1&&i!=order-1)
                  cout<<Lower[i]<<'\t';
               else if(i==order-1&&j!=i)
                  cout<<Intermediate2[j]<<'\t';
               else
                  cout<<0<<'\t';
           }  
   cout<<endl;
  }//打印Lower三角阵L
  cout<<endl; 
}  

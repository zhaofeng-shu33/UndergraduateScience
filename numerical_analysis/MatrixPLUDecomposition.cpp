#include<iostream>
#include<fstream>
#include <cstring>
#include<cmath>
#include<iomanip>
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
    void show_solution(){
         cout<<"Solution:"<<endl;
         for(int i=0;i<order;i++)
             cout<<std::fixed<<std::setprecision(2)<<solution_vector[i]<<endl;
    }      
  private: 
    double* solution_vector,*b;
};  
int main(){
  //例子见课本P42例题 
  double p[16]={2,1,1,0,4,3,3,1,8,7,9,5,6,7,9,8};
  double q[4]={1,2,2,-1};
  Linear_Equation my_linear_equation(4);
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
       // if(k==0)
        //cout<<initial_address[0]<<endl;
          //cout<<<<' '<<bendl<<endl;  
       swap(Permu+k,Permu+row);
      
         
         
         
        
  
      //上面的算法使用选主元的Gauss 消去法使得a[k][k]为所在列绝对值最大的元素。
      //同时记下每步使用的初等排列阵。  
      
     double l[order];
     for(int i = k+1; i < order; i++ ){
         l[i]=initial_address[i*order+k]/initial_address[k*order+k];
         Left.initial_address[i*order+k]=l[i];
         b[i]-=l[i]*b[k];
          for(int j=k+1; j< order; j++ )
              initial_address[i*order+j]-=l[i]*initial_address[k*order+j];
     }
          //用数组l对Left矩阵进行赋值。
      
       
  }  
  //上面的代码将矩阵化为上三角阵U，但需注意上三角阵主对角元没有归一化 
  solution_vector[order-1]=b[order-1]/initial_address[order*order-1]; //从最后一行开始求解。 
  for(int i=order-2; i>=0; i--){
      double tem=0;
      for(int j=i+1;j<order;j++)
          tem+=initial_address[i*order+j]*solution_vector[j]; 
      
      solution_vector[i]=(b[i]-tem)/initial_address[i*order+i];//cout<<solution_vector[i]<<endl;
  }      
  for(int i=0;i<order;i++){
      Left.initial_address[i*order+i]=1;
      for(int j=i+1;j<order;j++)
          Left.initial_address[i*order+j]=0;
  } //至此对下三角阵的赋值工作完成。
  cout<<endl;
  cout<<"L:"<<endl;
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++)
              cout<<Left.initial_address[i*order+j]<<'\t';
  cout<<endl;
  }//打印下三角阵L 
  cout<<endl;
  cout<<"U:"<<endl;
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++){
              if(j>=i)
              cout<<initial_address[i*order+j]<<'\t';
              else
              cout<<0<<'\t';
           }  
  cout<<endl;
  }//打印上三角阵U
  cout<<"P:"<<endl;
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++){
              if(Permu[i]==j)
              cout<<1<<'\t';
              else
              cout<<0<<'\t';
           } 
  cout<<endl;          
  }//打印排列阵 
}  

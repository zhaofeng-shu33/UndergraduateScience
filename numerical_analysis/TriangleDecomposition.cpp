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
double round_off(double x){//提高有效位数到5位可使得运算精度更高，若修改下面的10^5为10^3,则得到的解误差很大。 
  return floor(x * 100000) / 100000;
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
         cout<<"The order is "<<order<<endl;
         for(int i=0;i<order;i++)
             cout<<solution_vector[i]<<endl;
    }      
  private: 
    double* solution_vector,*b;
};  
int main(){
  double alpha=pow(10.0,-16);
  for(int n=2;n<=7;n++){
  
  double* p=new double[n*n];
  for(int i=0;i<n;i++)
     for(int j=0;j<n;j++){
         p[i*n+j]=0;
         for(int w=0;w<n;w++)
             p[i*n+j]+=1.0/((j+w+1)*(i+w+1));
     }  
  double* q=new double[n];
  for(int i=0;i<n;i++){
      q[i]=0;
     for(int j=0;j<n;j++)
          q[i]+=p[i*n+j];
  }
  for(int i=0;i<n*n;i++)
      p[i]+=alpha;
  Linear_Equation my_linear_equation(n);
  my_linear_equation.Set_Matrix(p);
  my_linear_equation.Set_Linear_Equation(q); 
 
//  my_linear_equation.Print_Linear_Equation();
  my_linear_equation.Solve();
  my_linear_equation.show_solution();
  delete [] p;
  delete [] q;
  }  
  char ch;
  cin>>ch;
  return 0;
}    
void Linear_Equation::Solve(){
   Matrix Left(order); 
    for(int k = 0; k <= order - 2; k++ ){ //从矩阵第一行到第order-1行进行 高斯消去
       if(initial_address[k*order+k]==0){   
         cout<<"Unable to decompose into triangle form directly!";
         break;
      }  
      //认为原矩阵不存在作高斯消去的因子出现零值的交换问题。  
      
      
     double l[order];
     for(int i = k+1; i < order; i++ ){
         l[i]=initial_address[i*order+k]/initial_address[k*order+k];
         Left.initial_address[i*order+k]=l[i];
         b[i]=b[i]-l[i]*b[k];
          for(int j=k+1; j< order; j++ )
              initial_address[i*order+j]=initial_address[i*order+j]-l[i]*initial_address[k*order+j];
     }
          //用数组l对Left矩阵进行赋值。
      
       
  }  
  //上面的代码将矩阵化为上三角阵U，但需注意上三角阵主对角元没有归一化 
  solution_vector[order-1]=b[order-1]/initial_address[order*order-1]; //从最后一行开始求解。 
  for(int i=order-2; i>=0; i--){
      double tem=0;
      for(int j=i+1;j<order;j++)
          tem=tem+initial_address[i*order+j]*solution_vector[j]; 
      
      solution_vector[i]=(b[i]-tem)/initial_address[i*order+i];//cout<<solution_vector[i]<<endl;
  }      
  /*for(int i=0;i<order;i++){
      Left.initial_address[i*order+i]=1;
      for(int j=i+1;j<order;j++)
          Left.initial_address[i*order+j]=0;
  } //至此对下三角阵的赋值工作完成。
  cout<<endl;
  
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++)
              cout<<Left.initial_address[i*order+j]<<'\t';
  cout<<endl;
  }//打印下三角阵L 
  cout<<endl;
  for(int i=0;i<order;i++){
           for(int j=0;j<order;j++){
              if(j>=i)
              cout<<initial_address[i*order+j]<<'\t';
              else
              cout<<0<<'\t';
           }  
  cout<<endl;
  }//打印上三角阵U
   */
}  

// mkdir -p build && g++ matrix_inverse_with_GJ_Method.cpp -o build/GJ
#include<iostream>
#include<fstream>
#include <cstring>
#include<cmath>
#include<iomanip>
using namespace std;
// Gauss-Jordan Method to reverse a Matrix
ofstream fout("GJ_Method_log.txt");
void swap(double* a,double* b){
  double t=*a;
  *a=*b;
  *b=t;
 }
 class Matrix{
  public:
    Matrix(int a){
      order=a;
      pos=new double[order*order];
    }
    ~Matrix(){}
    void SetMatrix(double* p){
      for(int i=0;i<order*order;i++){
          pos[i]=p[i];
      }  
    }
    void PrintMatrix(){
      for(int i=0;i<order;i++){
          for(int j=0;j<order;j++)
              cout<<pos[i*order+j]<<'\t';
          cout<<endl;
      }
    }     
  public:
    int order;
    double* pos;
};  
class AdjointMatrix: public Matrix{
  public:
    AdjointMatrix(int a):Matrix(a){ 
    Inverse=new double[a*a];
    }
    ~AdjointMatrix(){}
    void SetAdjointMatrix(double* a){
        for(int i=0;i<order*order;i++)
            Inverse[i]=a[i];
     
    }
    void Solve();
    void ShowAdjointMatrix(){
         for(int i=0;i<order;i++){
            for(int j=0;j<order;j++)
              fout<<std::setprecision(2)<<pos[i*order+j]<<'\t';
            fout<<'|'<<'\t';
            for(int j=0;j<order;j++)
              fout<<Inverse[i*order+j]<<'\t';
         fout<<endl;
         }
     fout<<endl;
    }      
  private: 
    double* Inverse;
};  
int main(){
  
  double p[16]={2, 1, -3, -1,
                3, 1, 0, 7,
                -1, 2, 4, -2,
                1, 0, -1, 5, 
                };
  double q[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
  AdjointMatrix MyAdjointMatrix(4);
  MyAdjointMatrix.SetMatrix(p);
  MyAdjointMatrix.SetAdjointMatrix(q);
  //MyAdjointMatrix.ShowAdjointMatrix();
  MyAdjointMatrix.Solve();
 
  fout.close();
  char ch;
  cin>>ch;
  return 0;
}    
void AdjointMatrix::Solve(){
   fout<<"The initial adjoint matrix takes the form: \n";
   ShowAdjointMatrix(); 
   for(int k = 0; k <=order-2; k++ ){ //从矩阵第一行到第order-1行进行 高斯消去
       double max1=pos[k*order+k];int row=k;
        for(int i = k; i < order; i++ ){
            if(abs(pos[i*order+k])>abs(max1)){
                 max1=pos[k*order+k];
                 row=i;
               }
        }  
        if(row!=k){
           for(int j=0; j<order; j++){
             swap(pos+k*order+j,pos+row*order+j);
             swap(Inverse+k*order+j,Inverse+row*order+j);
           }  
          
     
          fout<<"Exchanging the "<<row+1<<" row with the "<<k+1<<" row gives:\n";         
          ShowAdjointMatrix();  
       }
      //上面的算法使用选主元的Gauss 消去法使得a[k][k]为所在列为绝对值最大的元素。  
      
    double tem=pos[k*order+k];   
      for(int i=0;i<order;i++){         
          pos[k*order+i]/=tem;
          Inverse[k*order+i]/=tem;
      }
    fout<<"Normalization of the "<<k+1<<" row gives:\n"; 
    ShowAdjointMatrix();          
      //上面的代码解决将高斯消去的因子所在的行归一化的问题。 
     for(int i = k+1; i < order; i++ ){
         double tem=pos[i*order+k];
         for(int j=0; j< order; j++ ){
              pos[i*order+j]-=tem*pos[k*order+j];
              Inverse[i*order+j]-=tem*Inverse[k*order+j];
         }        
      }
      fout<<"Elimination of the elements below the ("<<k+1<<','<<k+1<<") position gives:\n";
      ShowAdjointMatrix();  
        
   } 
     for(int i=0;i<order;i++)
         Inverse[(order-1)*order+i]/=pos[order*order-1];
     pos[order*order-1]=1;
     fout<<"Normalization of the final row gives:\n"; 
       ShowAdjointMatrix();  
 //上面的代码将原矩阵化为上三角阵 

   for(int i=order-1;i>=1;i--){
                 for(int r=i-1;r>=0;r--){
                   for(int j=i;j>=0;j--)
                       Inverse[r*order+j]-=pos[r*order+i]*Inverse[i*order+j];
                  pos[r*order+i]=0;
                  }
      fout<<"Elimination of the elements above the ("<<i+1<<','<<i+1<<") position gives:\n";                                
      ShowAdjointMatrix();   
   }         
   //上面的代码将原矩阵化为单位阵。 
   //同时Inverse 变为原矩阵的逆阵。 
   fout<<"The matrix on the right hand of the vertical line is the required inverse matrix:\n";
   for(int i=0;i<order;i++){
            for(int j=0;j<order;j++)
              fout<<std::setprecision(3)<<Inverse[i*order+j]<<'\t'<<"   ";
         
     fout<<endl;
    }      
   
}  


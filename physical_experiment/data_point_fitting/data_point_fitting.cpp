#include<iostream>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<cmath>
#include<fstream>
#include<cstring>
// 用直线拟合数据点
// g++ data_point_fitting.cpp -lGL -lGLU -lglut -o build/dpf
const double Pi=3.14159, R = 8.314;
using namespace std;
int ww=400,wh=400;
void
bitmap_output(double x, double y,double z, char *string)
{
  int len, i;

  glRasterPos3f(x,y,z);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
  }
}
void init1(){
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0,ww,0,wh);
}
void drawArrow(double x,double y,double theta){//theta in degree
  glPushMatrix();
  glTranslatef(x,y,0);
  glRotatef(theta,0,0,1);
  glTranslatef(-x,-y,0);
  glBegin(GL_LINE_STRIP);
    glVertex2d(x-7,y+7);
    glVertex2d(x,y);
    glVertex2d(x-7,y-7);
  glEnd();
  glPopMatrix();
}
void drawIsotherm(double a,double b,double T,char* name){ 
  b*=pow(10.0,-5);
  double list[10000][2],max1=0,max2=0,V=2*b;
  int pos=0;
  for(int i=0;i<10000;i++){
     list[i][0]=(R*T)/(V - b) - a/(V*V);//represents the pressure;
     list[i][1]=(R*T*V)/(V - b) - a/V;//represents the PV
     V+=b/2;
     if(max1<list[i][0]){
        max1=list[i][0];
        pos=i;
     }  
     if(max2<list[i][1])
        max2=list[i][1];
        
  }
  cout<<std::fixed<<list[0][0]<<' '<<max1<<endl;
 
  double xscale=200/(2.5*pow(10.0,7)),yscale=200.0/2270;
  //cout<<xscale<<' '<<yscale<<endl;
  for(int i=0;i<10000;i++){  
     list[i][0]=list[i][0]*xscale+20;
     list[i][1]=list[i][1]*yscale+20;
  }
  glBegin(GL_LINE_STRIP);
    for(int i=0;i<10000;i++)
        glVertex2dv(list[i]);
  glEnd(); 
  if(list[pos][0]<370&&list[pos][1]<370)
  bitmap_output(list[pos][0],list[pos][1],0,name);
  else { for(int i=0;i<10000;i++)
          if(list[i][0]<300&&list[i][1]<300){
             pos=i;
             break;
          }
       bitmap_output(list[pos][0],list[pos][1],0,name);
       }  
           
}   
void display1(void){
  glTranslatef(20,20,0);
  
  glBegin(GL_LINES);
    glVertex2i(0,0);
    glVertex2i(200,0);
    glVertex2i(0,0);
    glVertex2i(0,200);
  glEnd();
  drawArrow(200,0,0);
  drawArrow(0,200,90);
  bitmap_output(0,0,0,"O");
  bitmap_output(-10,40,0,"21");
  bitmap_output(-10,80,0,"22");
  bitmap_output(-10,120,0,"23");
  bitmap_output(-10,160,0,"24");
  bitmap_output(-10,200,0,"y");
  bitmap_output(50,0,0,"20");
  bitmap_output(100,0,0,"40");
  bitmap_output(150,0,0,"60");
  bitmap_output(200,0,0,"x");
  
  ifstream fin("mydata.txt",ios::binary);
  
  double x[8],y[8];
  for(int i=0;i<8;i++){
    fin>>x[i];
    fin>>y[i];  
  }
  glPointSize(5);
  
  glBegin(GL_POINTS);
    for(int i=0;i<8;i++){
        glVertex2d(2.5*x[i],40*(y[i]-20));
        cout<<x[i]<<' '<<y[i]<<endl;
    }  
  glEnd();
  glBegin(GL_LINE_STRIP);
  double xnew=49.66;
   for(int i=0;i<1400;i++){
        glVertex2d(xnew,1.312*xnew-65.16);
        xnew+=0.1;
    }
  glEnd();   
  
  
  
  glFlush();
}
int main(int argc, char* argv[]){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(ww,wh);
  glutCreateWindow("Three-Dimensional Object Representations");
  glutDisplayFunc(display1);
  init1();
  glutMainLoop();
  return 0;
} 
 

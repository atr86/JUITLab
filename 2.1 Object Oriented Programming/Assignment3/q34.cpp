
#include <iostream>
#include <math.h>
using namespace std;

class Shape {
  string name;

public:
  Shape(string n = "Shape") 
{ name = n;
  cout<<endl<<name<<endl; }
virtual void setArea(float)=0;
virtual void getArea()=0;
virtual void getVol();
virtual void setVol();
};
void Shape::setVol(){}
void Shape::getVol(){}

class TwoD : public Shape {
  float area;

public:
  TwoD(string s="TwoD", float area = 0.0001f) : Shape(s)
{ this->area = area;}
virtual void getArea()=0;
void setArea(float a)
{
  area=a;
}
};
class Circle:public TwoD
{
int rad;
public:
Circle(int r=1):TwoD("Circle")
{
  rad=r;

}
void getArea()
{
  cout<<(M_PI*rad*rad);
  setArea(M_PI*rad*rad);
}
};
class Triangle:public TwoD
{
int a,b,c;
public:
Triangle(int a=1,int b=1,int c=1):TwoD("Triangle")
{
  this->a=a;
  this->b=b;
  this->c=c;
}
void getArea()
{
  float s=(a+b+c)/2.0;
  float a=sqrt(s*(s-a)*(s-b)*(s-c));
  cout<<a;
  setArea(a);
}
};
class Ellipse:public TwoD
{
int a,b;
public:
Ellipse(int a=1,int b=1):TwoD("Ellipse")
{
  this->a=a;
  this->b=b;
}
void getArea()
{
  float a=M_PI*a*b;
  cout<<a;
  setArea(a);
}
};

class ThreeD : public Shape {
  float vol;
  float area;
public:
  ThreeD(string s="ThreeD",float sa=0.0001f, float vol = 0.0001f) : Shape(s)
{ 
  this->vol = vol;
  this->area = sa;
}
virtual void getVol()=0;
virtual void getArea()=0;
void setArea(float a)
{
  area=a;
}
void setVol(float v)
{
  vol=v;
}
};

class Sphere:public ThreeD
{
int r;
public:
  Sphere(int r=1):r(r),ThreeD("Sphere"){}
 void getVol()
{
  float v=4/3.0*M_PI*r*r*r;
  cout<<v;
  setVol(v);
}
void getArea()
{
  float sa=4*M_PI*r*r;
  cout<<sa;
  setArea(sa);
}
};

class Cube:public ThreeD
{
int s;
public:
  Cube(int s=1):s(s),ThreeD("Cube"){}
 void getVol()
{
  float v=s*s*s;
  cout<<v;
  setVol(v);
}
void getArea()
{
  float sa=6*s*s;
  cout<<sa;
  setArea(sa);
}
};

int main()
{
  Shape* ptr[5];
  ptr[0]=new Circle(5);
  cout<<"Area "; 
  ptr[0]->getArea(); 
  ptr[1]=new Triangle(2,3,4);
  cout<<"Area "; 
  ptr[1]->getArea(); 
  ptr[2]=new Ellipse(1,2);
  cout<<"Area "; 
  ptr[02]->getArea(); 
  ptr[3]=new Sphere(5);
  cout<<"Area "; 
  ptr[3]->getArea(); 
  cout<<"Volume ";
  ptr[3]->getVol();
  ptr[4]=new Cube(5);
  cout<<"Area "; 
  ptr[4]->getArea(); 
  cout<<"Volume ";
  ptr[4]->getVol(); 

}



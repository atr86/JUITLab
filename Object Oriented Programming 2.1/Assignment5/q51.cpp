#include <iostream>
#include <math.h>
using namespace std;

class complex
{
    float real,img;
    public:
    complex(float r=0,float i=0)
     {
        real=r;
        img=i;
     }
  complex(complex& c)
{
  real=c.real;
  img=c.img;
}
    float mod(complex& c)
{
      return sqrt(real*real+img*img);
}
    friend ostream& operator<<(ostream& os, const complex c)
{
  os<<c.real<<"+"<<c.img<<"i   ";
  return os;
}

};

class stack{
int *buffer,top;
public:
stack(int);
void push(int);
int pop();
void disp();
};
stack :: stack(int n)
{
  buffer= (int*)malloc(n*sizeof(int));
  top=-1;
}
void stack :: push(int p)
{
  if(top==-1)
    top=0;
  else
    top++;
  *(buffer+top)=p;

}
int stack :: pop()
{
  if(top==-1)
    return -9999;
  else
  {
    top--;
    return *(buffer+top+1);
  }
}
void stack :: disp()
{
  int i;
  for(i=0;i<top;i++)
    {
      cout<<*(buffer+i)<<endl;
    }
}



template<class T>
void swap1(T& x, T& y)
{
  T z;
  z=x;
  x=y;
  y=z;
}
template<>
void swap1<complex>(complex& x, complex& y)
{
  complex z;
  z=x;
  x=y;
  y=z;
}

template<> 
void swap1<stack> (stack& x, stack& y)
{
  stack z(100);
  int i=0,x1=0,y1=0;
  while((i=x.pop())!=-9999)
    {
      z.push(i);
      x1++;
    }
  i=0;
  while((i=y.pop())!=-9999)
    {
      z.push(i);
      y1++;
    }
  i=0;
  while(y1>0)
    {
      y1--;
      i=z.pop();
      x.push(i);
    }
  i=0;
  while((i=z.pop())!=-9999)
    {
      y.push(i);
    }
  
}


int main()
{
  stack s1(11);
  stack s2(11);
  int i;
  for(i=0;i<10;i++)
    {
      s1.push(0+i);
      s2.push(10+i);
    }
  cout << "Stack s1 before swap:" << endl;
  s1.disp();
  cout << "Stack s2 before swap:" << endl;
  s2.disp();

  // Swap the two stacks
  swap1<stack>(s1, s2);

  cout << "Stack s1 after swap:" << endl;
  s1.disp();
  cout << "Stack s2 after swap:" << endl;
  s2.disp();

  complex c1(2,3);
  complex c2(4,5);
  cout<<c1<<" "<<c2<<endl;
  swap1<complex>(c1,c2);
  cout<<c1<<" "<<c2<<endl;

  int a=2,b=3;
  cout<<a<<"  "<<b<<endl;
  swap1(a,b);
  cout<<a<<"  "<<b<<endl;
  
}
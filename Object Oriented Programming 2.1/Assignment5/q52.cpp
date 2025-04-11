// Create a C++ template class for implementation of Stack data structure. Create a Stack of integers
// and a Stack of complex numbers created earlier (code may be reused). Perform some push and pop
// operations on these stacks. Finally print the elements remained in those stacks.

#include <iostream>
using namespace std;
template<class T>
class Stack
{
T *buffer;
int top;
public:
// Stack(int);
// void push(int);
// int pop();
// void disp();
 Stack(int n)
{
  buffer= (T*)malloc(n*sizeof(T));
  top=-1;
}
void  push(T t)
{
  if(top==-1)
   top=0;
  else
   top++;
  *(buffer+top)=t;

}
T pop()
{
  if(top==-1)
    return *(buffer);
  else
  {
    top--;
    return *(buffer+top+1);
  }
}
void disp()
{
  int i;
  for(i=0;i<=top;i++)
    {
      cout<<*(buffer+i)<<endl;
    }
}
};

class complex
{
    float real,img;
    public:
    complex(float r=0,float i=0)
     {
        real=r;
        img=i;
     }


void disp()
{
    cout<<real<<"+"<<img<<"i"<<endl;

}
friend ostream& operator<<(ostream& os, const complex& c)
{
  os<<c.real<<"+"<<c.img<<"i   ";
  return os;
}
friend istream& operator>>(istream& is,  complex& c)
{
  is>>c.real;
  is>>c.img;
  return is;
}
};

int main()
{
  Stack<int> s(10);
  cout<<"Pushed in 2 3 4 5"<<endl;
  s.push(2);
  s.push(3);
  s.push(4);
  s.push(5);
  s.disp();
  cout<<"Popped out "<<s.pop()<<" "<<s.pop()<<endl;
  s.disp();

  Stack<complex> st(7);
  complex ptr;
  int i;
  for(i=0;i<5;i++)
    {
      cin>>ptr;
      st.push(ptr);
    }
  cout<<"Popped out "<<st.pop()<<" "<<st.pop()<<endl;
  st.disp();
}

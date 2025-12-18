#include <iostream>
using namespace std;

class B
{
int b;
public:
B(int b1=0){
  b=b1;
}
void disp()
{
  cout<<"B="<<b<<endl;
}
virtual ~B()
{
  cout<<"B destroyed";
}
};

class C: public B{
int  c;
public:
C(int c1=0):B(c1+1)
{
  c=c1;
}
void disp()
{
  B::disp();
  cout<<"C="<<c<<endl;
}
~C()
{
  cout<<"C is destroyed";
}
};
void run()
{
  try{
  B* ptr= new C(1);
  ptr->disp();
  delete (ptr);
  throw 1;
  }
  catch(int r)
  {
      cout<<endl<<"Child instance deleted";
  }
}


int main()
{
  run();
  
}

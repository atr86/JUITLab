#include <iostream>
using namespace std;
#include <math.h>
/*Implement a class “Quadratic” that represents second-degree polynomial i.e. polynomial of type
ax2+bx+c. The class will require three data members corresponding to a, b and c. Implement the
following:
a. A constructor (including a default constructor which create a null polynomial)
b. Overload the addition operator to add two polynomials of degree 2.
c. Overload << and >> operators to print and read polynomials.
d. A function to compute the value of polynomial for a given x.
e. A function to compute roots of the equation ax2+bx+c=0. Remember, root may be a complex
number. You may implement “Complex” class to represent root of the quadratic equation.*/





class Quadratic
{
  int a, b, c;
  public:
  class complex
  {
          public:
        float real,img;

      complex(float r=0,float i=0)
        {
            real=r;
            img=i;
        }


    void disp()
    {
          cout<<real<<"+"<<img<<"i"<<endl;

    }
  };
  Quadratic(int a=0, int b=0, int c=0)
  {
      this->a=a;
      this->b=b;
      this->c=c;
  }	    
  Quadratic operator+(Quadratic q)
  {
      Quadratic fin(a+q.a,b+q.b,c+q.c);
      return fin;
  }
  int func(int x)
  {
      return a*x*x+b*x+c;
  }
  friend ostream& operator<<(ostream& os, const Quadratic obj)
    {

        os<<obj.a<<"x^2+";
        os<<obj.b<<"x+";
        os<<obj.c<<endl;
        return os;
    }
    friend istream& operator>>(istream& is, Quadratic& obj)
    {

        is>>obj.a;
        is>>obj.b;
        is>>obj.c;

        return is;
    }
    void roots()
     {
        int dis=b*b-4*a*c;
        if(dis>=0)
        {
            float r1=((-1)*b+sqrt(dis))/(2*a);
            float r2=((-1)*b-sqrt(dis))/(2*a);
            cout<<r1<<","<<r2;
        }
        else
        {
            complex c1,c2;
            c1.real=((-1)*b)/(2*a);
            c2.real=((-1)*b)/(2*a);
            c1.img=(-1)*sqrt(-dis)/(2*a);
            c2.img=sqrt(-dis)/(2*a);
            c1.disp();
            c2.disp();
        }
    }

  };




  int main()  
  {

    Quadratic q1,q2,q3;
    cin>>q1;
    cin>>q2;
    q3=q1+q2;
    cout<<q1;
    cout<<q2;
    cout<<q3;
    cout<<"Roots of q1"<<endl;
    q1.roots();
   } 



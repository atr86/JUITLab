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


void disp()
{
    cout<<real<<"+"<<img<<"i"<<endl;

}
complex operator+(complex& c)
{
    float r=real + c.real;
    float i=img  + c.img;
    complex sum(r,i);
    return sum;
}
complex operator-(complex& c)
{
    float r=real - c.real;
    float i=img  - c.img;
    complex diff(r,i);
    return diff;
}

complex operator*(complex& c)
{
    float r=real*c.real-img*c.img;
    float i=real*c.img+c.real*img;
    complex prod(r,i);
    return prod;
}

complex operator/(complex& c)
{
    complex con=~c;//this line is imp as we cannot binf
    complex div=(*this)*con;
    div.real/=!c;
    div.img/=!c;
    return div;
}

float operator!()
{
    return sqrt(real*real+img*img);
}

complex operator~()
{
     complex c(real,-img);
     return c;
     
}
};

int main()
{
    complex c1(1,2);
    complex c2(2,3);
    complex sum=c1+c2;
    complex diff=c1-c2;
    complex prod=c1*c2;
    complex div=c1/c2;
    c1.disp();
    c2.disp();
    cout<<"DMAS of 2 complex numbers is = "<endl;
    div.disp();
    prod.disp();
    sum.disp();
    diff.disp();
    
    
    
}


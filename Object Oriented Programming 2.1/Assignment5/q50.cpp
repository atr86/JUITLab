// 50. Write a template function max() that is capable of finding maximum of two things (that can be
// compared). Used this function to find (i) maximum of two integers, (ii) maximum of two complex
// numbers (previous code may be reused). Now write a specialized template function for strings (i.e. char
// *). Also find the maximum of two strings using this template function.

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
template<class T>
T& max(T& t1, T& t2)
{
    if(t1>t2)
      return  t1;
    else
      return  t2;
}

template<>
string& max<string>(string& s1, string& s2)
{
  if(s1.compare(s2))
    return s1;
  else
    return s2;
    
}

  int main()
  {
    int a=2, b=3;
    cout<<"max of  "<<a<<"  &  "<<b<<"  is  "<<max(a,b)<<endl;
    float a1=2.9f, b1=3.5f;
    cout<<"max of  "<<a1<<"  &  "<<b1<<"  is  "<<max(a1,b1)<<endl;
    complex c1(1.1f,2.2f),c2(2.3f, 0.8f);
    cout<<"max of  "<<c1<<"  &  "<<c2<<"  is  on mod value "<<max(c1.mod(c1),c2.mod(c2))<<endl;
    string a2="hello",b2="friends";
    cout<<"max of  "<<a2<<"  &  "<<b2<<"  is  "<<max<string>(a2,b2)<<endl;
   return 0;
  }


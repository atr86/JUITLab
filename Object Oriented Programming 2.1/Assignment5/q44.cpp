// 44. Two integers are taken from keyboard. Then perform division operation. Write a try block to throw
// an exception when division by zero occurs and appropriate catch block to handle the exception thrown.
#include <iostream>
using namespace std;

int main()
{
  int a, b;
  cout<<"Enter 2 integers";
  cin>>a>>b;
  try
    {
      if(b==0)
        throw b;
      else
        cout<<a/b;
    }
    catch(int e)
    {
      cout<<"You have tried to divide by "<<e;
    }
  }
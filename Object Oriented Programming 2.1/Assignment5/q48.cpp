// 48. Write a Garage class that has a Car that is having troubles with its
// Motor. Use a function- level try block in the Garage class constructor to
// catch an exception (thrown from the Motor class) when its Car object is
// initialized. Throw a different exception from the body of the Garage
// constructor s handler and catch it in main( ).
#include <iostream>
using namespace std;

class Motor {
public:
  Motor() { throw "Motor is not ready yet"; }
};

class Car {
public:
  Car() { Motor m; }
};
class Garage
{
public:
Garage()
{
  try{
    Car c;
  }
    catch(const char* s)
    {
      cout<<"Car didnot start \n";
      cout<<"Motor is not ready yet"<<endl;
      throw -1;
    }
}

};
int main()
{
  try{
    Garage g;
    cout<<"Garage is Empty";
  }
    catch(int n)
    {
      cout<<"Garage is not empty";
    }
  }

// 46. Create a class with member functions that throw exceptions. Within this
// class, make a nested class to use as an exception object. It takes a single
// const char* as its argument; this represents a description string. Create a
// member function that throws this exception. (State this in the function s
// exception specification.) Write a try block that calls this function and a
// catch clause that handles the exception by displaying its description string.
#include <iostream>
using namespace std;
class Category {

  int age;

public:
  class Excepn {

  public:
    Excepn(const char *ch) { cout << ch<<endl; }
  };
  Category(int age) { this->age = age; }
  void chess() {
    cout << "For chess, Your child will fall in category ";
    switch (age) {
    case 11:
    case 12:
    case 13:
      throw Excepn("UNDER 13");
      break;
    case 14:
    case 15:
      throw Excepn("UNDER 15");
      break;
    case 16:
    case 17:
      throw Excepn("UNDER 17");
      break;
    case 18:
    case 19:
      throw Excepn("UNDER 19");
      break;
    case 20:
    case 21:
    case 22:
    case 23:
      throw Excepn("UNDER 23");
      break;
   default:
      throw Excepn("OPEN NO AGE");
      break;
      
    }
  }
  void school() {
    cout << "In school, your child will read in " ;
    switch (age) {
    case 11:
    case 12:
    case 13:
    case 14:
      throw Excepn("Middle School");
      break;
    case 15:
    case 16:
      throw Excepn("Secondary School");
      break;
    case 17:
    case 18:
      throw Excepn("Higher Secondary School");
      break;
    case 19:
    case 20:
    case 21:
    case 22:
      throw Excepn("Undergraduate School");
      break;
  default:
      throw Excepn("Graduate School");
    }
  }
};
int main()
{
  int age;
  cout<<"Enter your child's age";
  cin>> age;
  Category c(age);
  try{
  c.school();
   }
  catch(Category::Excepn e)
    {

    }
   try{
    c.chess();
     }
    catch(Category::Excepn e)
      {

      }
}
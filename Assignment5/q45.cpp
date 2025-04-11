// 45. Write a C++ program to demonstrate the use of try, catch block with the
// argument as an integer and string using multiple catch blocks.

#include <iostream>
using namespace std;

int main()
{
  int age;
  string val;
  cout<<"Enter your grade of pay(A,B...) and age";
  cin>>val>>age;
  try{
    if(val=="A"|| val=="B")
      throw val;
    else if(age<30)
      throw age;
    else
      cout<<"You are eligible for bonus";
  }
    catch(string val)
    {
      cout<<"You are not eligible for bonus as you are at top of grade pay";
    }
    catch(int age)
    {
      cout<<"You are NOT passing age criteria";
    }
  return 0;
}
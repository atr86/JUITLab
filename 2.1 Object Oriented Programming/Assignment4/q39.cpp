// class INT {
// int i;
// public :
// INT(int a):i(a){}
// ~INT() {}
// };
// int main() {
// int x = 3;
// INT y = x;
// y++ = ++y;
// x = y;
// return 0;
// }

#include <iostream>
using namespace std;

class INT {
  int i;

public:
  INT(int a) : i(a) {}
  ~INT() {}
  
INT& operator++(int)
  { this->i++;
    return *(this);
  }
  INT operator++()
{
  INT I(i);
  I.i++;
  i++;
  return I;
  
}
void operator=(const INT &I)
{
  i=I.i;
}
  operator int()
{ return i; }
};

int main() {
  int x = 3;
  INT y = x;
  y++ = ++y;
  x = y;
  cout<<x;
  return 0;
}
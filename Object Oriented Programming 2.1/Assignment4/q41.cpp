#include <iostream>
using namespace std;
class Integer
{
int i;
    public:
    Integer(int i=0)
    {
        this->i=i;
    }
    Integer operator++(int)
{
        Integer Int(this->i);
        this->i++;
        return Int;
}
    Integer operator+(Integer I)
{
    Integer Int(this->i+I.i);
    return Int;
}
operator int()
{
    return i;
}
friend ostream& operator<<(ostream& os, const Integer I)
{
    os<<"i for this object is "<<I.i<<endl;
    return os;
}

};

int main() 
{
  Integer a = 4, b = a, c;
  c = a + b++;
  int i = a;
  cout << a << b << c;
  return 0;
}



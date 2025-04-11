#include <iostream>
using namespace std;

// 40. Design and implement class(es) to support the following main program.
// int main() {
// IntArray i(10);
// for(int k = 0; k < 10; k++)
// i[k] = k;
// cout << i;
// return 0;
// }

class IntArray
{
  int* a;
  int size;
  public:
  IntArray(int s)
{
  a=(int*)malloc(sizeof(int)*s);
  size=s;
}
friend ostream& operator<<(ostream& os, IntArray i)
{
  for(int j=0;j<i.size;j++)
    {
      os<<i[j]<<",";
    }
  os<<endl;
  return os;
}
int& operator[](int k)
{
  if(k<0)
    return a[0];
  else if(k>=size)
    return a[size-1];
  else
    return a[k];
}
};

int main() {
IntArray i(10);
for(int k = 0; k < 10; k++)
i[k] = k;
   cout << i;
  cout<<"Enter 10 random indices of array"<<endl;
  int p;
for(int k=0;k<10;k++)
  {
    cin>>p;
    cout<<" "<<i[p]<<endl;
  }
return 0;
}


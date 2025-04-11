// 49. Vehicles may be either stopped of running in a lane. If two vehicles are running in opposite direction
// in a single lane there is a chance of collision. Write a C++ program using exception handling to avoid
// collisions. You are free to make necessary assumptions.

#include <iostream>
using namespace std;
class Car
{
  bool dir;//0 if up, 1 if down
  int no;
  public:
  Car(bool dir, int number)
{
      this->dir=dir;
      no=number;
}
   bool check(Car c1, Car c2)
  {
  return c1.dir^c2.dir;
  }
  int carno(Car c)
{
  return c.no;
}
};

int main()
{
  int i=0, no,j;
  char dir;
  cout<< "Enter the value of CAR NO and direction U OR D";
  Car *c[10];// array of pointers
  while(i<10)
    {
      
      try {
            cin>>no;
            cin>>dir;
            for(j=0;j<i;j++)
              {
                bool b=c[i]->check(*c[i],*c[j]);
                int  no=c[i]->carno(*c[i]);
                
                if(b)
                  throw  no;                 
              }
            c[i]= new Car(dir=='U'?0:1,no);
          i++;
      }
        catch(int val)
        {
          cout<<"Car no"<< val<<" must stop else collide";
        }
        
      }
    return 0;
    }


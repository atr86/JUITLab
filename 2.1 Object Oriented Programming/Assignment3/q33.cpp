// 33.Write class definitions for the following class hierarchy
// Shape2D
// Circle Rectangle
// The Shape2D class represents two dimensional shapes that should have pure
// virtual functions area(), perimeter() etc. Implement these functions in
// Circle and Rectangle. Also write proper constructor(s) and other functions
// you think appropriate in the Circle and Rectangle class. Now create an array
// of 5 Shape2D pointers. Create 3 Circle and    2 Rectangles objects and place
// their addresses in that array. Use a loop to print area and perimeter of all
// shapes on this array.



#include <iostream>
#include <math.h>
using namespace std;

class Shape2D {
public:
float a;
int p;
  Shape2D() {
   cout<<"ShapeCreated";
  }

  virtual void area() = 0;
  virtual void peri() = 0;
};

class Circle : public Shape2D {
  int rad;

public:
  Circle(int r = 1) 
{ rad = r;
cout<<"Circle Created";}
  void area() 
	{
    a=M_PI*rad*rad;
		cout<<"Area="<<a<<endl;
  }
void peri() 
{
	p=2*M_PI*rad;
	cout<<"Perimeter="<<p<<endl;
}  
};

class Square : public Shape2D {
	int s;

public:
	Square(int a = 1) 
{ s=a;
cout<<"Square Created";}
	void area() 
	{
		a=s*s;
		cout<<"Area="<<a<<endl;
	}
void peri() 
{
	p=4*s;
	cout<<"Perimeter="<<p<<endl;
}  
};


int main()
{
	Shape2D* p[5];
	p[0]=new Circle(1);
	p[1]=new Circle(2);
	p[2]=new Circle(3);
	p[3]=new Square(1);
	p[4]=new Square(2);
	int i;
	cout<<endl;
	for(i=0;i<5;i++)
		{
			
			p[i]->area();
			p[i]->peri();
		}
}
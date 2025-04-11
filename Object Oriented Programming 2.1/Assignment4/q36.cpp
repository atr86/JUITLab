/*Write a class “Point” which stores coordinates in (x, y) form. Define necessary constructor, destructor
and other reader/writer functions. Now overload ‘-’ operator to calculate the distance between two
points.*/


#include <iostream>
#include <math.h>
using namespace std;

class Point
{
    int x;
    int y;
    public:
    Point(int a=0, int b=0)
    {
        x=a;
        y=b;
    }

Point(Point& a1)
{
    x=a1.x;
    y=a1.y;
}
    float operator-(Point& p)
    {
        float d=(x-p.x)*(x-p.x)+(y-p.y)*(y-p.y);
        d=sqrt(d);
        return d;
    }
    
    int get_x()
    {
        return x;
    }
    int get_y()
    {
        return y;
    }
    void set_x(int xn)
    {
        x=xn;
    }
        
    void set_y(int yn)
    {
        y=yn;
    }
    
    ~Point()
    {
        cout<<"The point ("<<x<<','<<y<<") is no more existent on R2 plane"<<endl;
    }
};

int main()
{
    int x1,y1,x2,y2;
    cout<<"Enter 2 points";
    cin>>x1>>y1;
    cin>>x2>>y2;
    Point p1(x1,y1);
    Point p2(x2,y2);
    cout<<"Distance= "<<(p1-p2)<<endl;           
} 
 
 


    
    

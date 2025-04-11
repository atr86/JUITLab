
interface Shape 
{
    double area();
    void move(int dx, int dy);
    void rotate(double theta );
    void draw(double[][] p);
} 

class Circle implements Shape
{
    double x,y;
    int r;
    Circle(int r)
    {
        this.r=r;
        x=y=0;
    }
    
    public double area()
    {
        return Math.PI*r*r;
    }
    public void move(int dx, int dy)
    {
        x+=dx;
        y+=dy;
    }
    public void rotate(double theta)
    {
        // doesnot matter
        
    }
    public void draw(double[][] p)
    {
        x=p[0][0];
        y=p[0][1];
    }
}

class Rectangle implements Shape
{
    double v[][];
    int a,b;
    
    Rectangle(int a, int b)
    {
        this.a=a;
        this.b=b;
        v= new double[4][2];
    }
    public double area()
    {
        return a*b;
    }
    public void move(int dx, int dy)
    {
        int i;
        for(i=0;i<4;i++)
        {
            v[i][0]+=dx;
            v[i][1]+=dy;
        }
    }
    public void rotate(double theta)
    {
        int i; double x=0,y=0;
        for(i=0;i<4;i++)
        {
           x =( v[i][0]*Math.cos(theta)-v[i][1]*Math.sin(theta)) ;
           y =( v[i][0]*Math.sin(theta)+v[i][1]*Math.cos(theta)) ;
           v[i][0]=x;
           v[i][1]=y; 
        }
    }
    public void draw(double[][] p)
    {
        v=p;
    }
    void display()
    {
        int i;
        System.out.println("Coodinates are");
        for(i=0;i<4;i++)
        {
            System.out.println(v[i][0]+" , "+v[i][1]);
        }
         System.out.println("Side lengths are "+ a+" * "+b);
    }
}

public class q14 {
    public static void main(String args[])
    {
        Circle c= new Circle(5);
        double c1[][]={{0,0}};
        c.draw(c1);
        System.out.println("We have a circle with centre"+c.x+","+c.y +" radius "+c.r);
        c.move(4,5);
        c.rotate(30);
        System.out.println("Now moved by 4,5 and rotate by 30 degree to get a circle with  "+c.x+","+c.y+" and radius "+ c.r+" and area = "+c.area());
        Rectangle r= new Rectangle(4,3);
        double[][] c2= {{0,0},{4,0},{4,3},{0,3}};
        r.draw(c2);
        System.out.println("We have a Rectangle with following details ");
        r.display();
        r.move(5,6);
        r.rotate(30);
        System.out.println("Now moved Rectangle by 5,6 with following details ");
        r.display();
    }
}



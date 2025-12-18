// Imagine a toll booth and a bridge. Cars passing by the booth are expected to pay an amount of Rs.
// 50/- as toll tax. Mostly they do but sometimes a car goes by without paying. The toll booth keeps
// track of the number of the cars that have passed without paying, total number of cars passed by,
// and the total amount of money collected. Execute this with a class called “Tollbooth” and print
// out the result as follows:
// The total number of cars passed by without paying.
// Total number of cars passed by.
// Total cash collected.


class Tollbooth 
{
    private int coll;
    private int total;
    private String unpaid[];
    int k;
    Tollbooth(int max)
    {
        coll=0;
        total=0;
        unpaid=new String[max];
        k=0;
    }
    void carPassed(String n,boolean receive)
    {
        // System.out.println(n);
        // System.out.println(receive);
        if(receive==true)
        {
            coll+=50;
            
        }
        else
        {
            unpaid[k++]=n;
        }
        total++;
    }
    void display()
    {
        System.out.println("The total number of cars passed by without paying is "+ k);
        System.out.println("Total number of cars passed by is "+total);
        System.out.println("Total cash collected is "+coll);
        
    }
}

public class q15
{
    public static void main(String args[])
    {
        Tollbooth t= new Tollbooth(10);
        int i;
        double m1,m2;
        boolean rec=false;
        for(i=0;i<10;i++)
        {
            m1=Math.random();
            m2=Math.random();
            rec= (m1>=0.5);
            m2=m2*Math.pow(10,8);
            t.carPassed("WB"+(int)m2,rec);
        }
        t.display();
    }
}


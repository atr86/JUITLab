package ooslab;
import java.util.Scanner;
// 11. Implement a class for “Date”. Write member functions for (i) getting the previous day, (iv)
// getting the next day, (iii) printing a day
// There should be four constructors: (i) day, month and year are initialized to 01, 01, 1970; (ii) day
// is initialized to user specified value but month and year are initialized to 01, 1970; (iii) day,
// month are initialized to user specified value but year is initialized to 1970; (iv) day, month and
// year are initialized to user defined values.
// Also, write a main() function to (i) create a date object; (ii) print the next and the previous day.

class Date
{
    int d, m, y;
    Date()
    {
        d=1;
        m=1;
        y=1970;
    }
    Date(int d, int m)
    {
        this.d=d;
        this.m=m;
        y=1970;
    }
    Date(int d, int m,int y)
    {
        this.d=d;
        this.m=m;
        this.y=y;
    }
    void display()
    {
        System.out.println(d+"/"+m+"/"+y);
    }
}


public class q11
{
    static int mon[]= {31,28,31,30,31,30,31,31,30,31,30,31};
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the Date: dd,mm,yyyy");
        Date obj= new Date(sc.nextInt(), sc.nextInt(), sc.nextInt());
        Date prev= calc_prev(obj);
        Date next= calc_next(obj);
        System.out.println("Present Date");
        obj.display();
        System.out.println("Previous Date");
        prev.display();
        System.out.println("Next Date");
        next.display();
        sc.close();
    }
    static Date calc_prev(Date obj)
    {
        {
            if(obj.y%400==0||obj.y%100!=0 && obj.y%4==0)
            mon[1]=29;
            Date prev= new Date(obj.d-1, obj.m, obj.y);
            if(prev.d==0)
            {
                prev.m--;
                if(prev.m==0)
                {
                    prev.y--;
                    prev.d=31;
                    prev.m=12;
                }
                else
                    prev.d=mon[prev.m-1];

            }
            return prev;
        }
    }
    static Date calc_next(Date obj)
    {
        if(obj.y%400==0||obj.y%100!=0 && obj.y%4==0)
        mon[1]=29;
        Date next= new Date(obj.d+1, obj.m, obj.y);
        if(next.d>mon[next.m-1])
        {
            next.d=1;
            next.m++;
            if(next.m>12)
            {
                next.y++;
                next.m=1;
            }
        }
        return next;
    }
}
 
 






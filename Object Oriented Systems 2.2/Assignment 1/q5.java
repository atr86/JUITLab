/*Write a class to represent complex numbers with necessary constructors. Write member
functions to add, multiply two complex numbers.
There should be three constructors: (i) to initialize real and imaginary parts to 0; (ii) to initialize
imaginary part to 0 but to initialize the real part to user defined value; (iii) to initialize the real
part and the imaginary part to user defined values.
Also, write a main() function to (i) create two complex numbers 3+2i and 4-2i; (ii) to print the
sum and product of those numbers. */

class complex
{
    int real;
    int img;
    complex()
        {
            real=0;
            img=0;
        }
    complex(int r)
    {
        real=r;
        img=0;
    }
    complex(int r, int i)
    {
        real=r;
        img=i;
    }
    complex add(complex c)
    {
        complex sum=new complex(real+c.real, img+c.img);
        return sum;
    }
    complex multiply(complex c)
    {
        complex pdt=new complex(real*c.real- img+c.img, real*c.img+img*c.real);
        return pdt;
    }
    void display()
    {
        System.out.println(real+ ((img>=0)?"+":"")+img+"i");
    }
}

public class q5 {

     public static void main(String[] args) {
        complex c1= new complex(3,2);
        complex c2= new complex(4, (-2));
        complex sum=c1.add(c2);
        complex pdt= c2.multiply(c2);
        System.out.println("Sum");
        sum.display();
        System.out.println("Product");
        pdt.display();

     }
}
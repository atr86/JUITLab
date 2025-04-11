package ooslab;

// Create an abstract class “Publication” with data members ‘noOfPages’, ‘price’, ‘publisherName’
// etc. with their accessor/modifier functions. Now create two sub-classes “Book” and “Journal”.
// Create a class Library that contains a list of Publications. Write a main() function and create
// three Books and two Journals, add them to library and print the details of all publications.

abstract class Publication
{
    protected String name;
    private int noOfPages;
    private int price;
    private String publisherName;

    void setPg(int x)
    {
        noOfPages=x;
    }
    void setPrice(int x)
    {
        price=x;
    }
    void setPubName(String s)
    {
        publisherName=s;
    }
    void setName(String s)
    {
        name=s;
    }
    abstract void getName();
    public void getPg()
    {
        System.out.println("The no of pages of "+name+" is "+noOfPages);
    }
    
    public void getPrice()
    {
        System.out.println("The price of "+name+" is "+price);
    }
     
    public void publisherName()
    {
        System.out.println(name+" is published by "+publisherName);
    }
}

class Book extends Publication
{
    Book(String n, int pg, int p, String pubName)
    {
        super();
        setName(n);
        setPg(pg);
        setPrice(p);
        setPubName(pubName);
    }
    public void getName()
    {
        System.out.println("This is a book named "+ name);
    }
}
class Journal extends Publication
{
    Journal(String n, int pg, int p, String pubName)
    {
        super();
        setName(n);
        setPg(pg);
        setPrice(p);
        setPubName(pubName);
    }
    public void getName()
    {
        System.out.println("This is a journal named "+ name);
    }
}  

class Library
{
    Publication p[]; int top;
    Library(int max)
    {
        p= new Publication[max];
        top=-1;
    }
    void add(Publication pub)
    {
        if(top==p.length-1)
            System.out.println("Max no of Pub reached");
        else
        {
            p[++top]=pub;
        }
    }
    void display()
    {
        int i;
        for(i=0;i<=top;i++)
        {
            p[i].getName();
            p[i].getPrice();
            p[i].getPg();
            p[i].publisherName();
            System.out.println();
        }
    }
}


public class q7
{
    public static void main(String args[])
    {
        Library lib = new Library(10);
        Book a = new Book("The Count of Monte Cristo",400, 350, "Fingerprint Classics");
        Book b= new Book("The Very Hungry Caterpillar",285, 300,"World of Eric Carle");
        Book c= new Book("The Cat in the Hat", 380, 450, "Random House");
        Journal d= new Journal("IEEE Transactions on Pattern Analysis and Machine Intelligence (TPAMI)",500, 2000, "IEEE Computer Society");
        Journal e= new Journal("Nature", 400, 1500, "Springer Nature");
        lib.add(a);
        lib.add(b);
        lib.add(c);
        lib.add(d);
        lib.add(e);
        lib.display();
    }
}

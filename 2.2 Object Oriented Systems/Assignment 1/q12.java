// Implement a class for a “Student”. Information about a student includes name, roll no and an array
// of five subject names. The class should have suitable constructor and get/set methods.
// Implement a class “TabulationSheet”. A tabulation sheet contains roll numbers and marks of each
// student for a particular subject. This class should have a method for adding the marks and roll no
// of a student.
// Implement a class “MarkSheet”. A mark sheet contains marks of all subjects for a particular
// student. This class should have a method to add name of a student and marks in each subject.
// Write a main() function to create three “Student” objects, Five “Tabulationsheet” objects for Five
// subjects and three “Marksheet” object for three students. Print the mark sheets.




class Student
{
    String name;
    int roll;
    String sub[];
    Student(String n, int r, String s[])
    {
        name=n;
        roll=r;
        sub=s;
    }
    void display()
    {
        System.out.println("Name is "+name+" Roll no "+roll+" and has obtained marks in his/her following subjects----");
        
    }

}   
class Marksheet extends Student
{
    int mark[];
    Marksheet(String n, int r, String s[], int m[] )
    {
        super(n,r,s);
        mark=m;
    }
    void display()
    {
        super.display();
       int i;
       for(i=0;i<sub.length;i++)
        {
            System.out.println(sub[i]+" - "+mark[i]);
        }
    }
}
class TabulationSheet
{
    int roll[];
    int mark[];
    TabulationSheet(int[] r, int[] m)
    {
        roll=r;
        mark=m;
    }
}

public class q12
{
 
    public static void main(String args[])
    {
        Marksheet a,b,c;
        String s[]= {"Phy", "Chem", "Math", "CS", "PT"};
        int m1[]= {86, 89, 92, 78, 90};
        int m2[]= {76, 85, 94, 89, 90};
        int m3[]= {87, 78, 93, 78, 98};
        a= new Marksheet("Ram", 1001, s ,m1);
        b= new Marksheet("Shyam",1002, s, m2);
        c= new Marksheet("Jodu", 1003, s, m3);
        int[] t1={86, 76, 87};
        int[] t2={89, 85, 78};
        int[] t3={92, 94, 93};
        int[] t4={78, 89, 78};
        int[] t5={90, 90, 98};
        int[] r1={1001, 1002, 1003};
        int[] r2={1001, 1002, 1003};
        int[] r3={1001, 1002, 1003};
        int[] r4={1001, 1002, 1003};
        int[] r5={1001, 1002, 1003};
        TabulationSheet s1= new TabulationSheet(t1, r1);
        TabulationSheet s2= new TabulationSheet(t2,r2);
        TabulationSheet s3= new TabulationSheet(t3,r3);
        TabulationSheet s4= new TabulationSheet(t4,r4);
        TabulationSheet s5= new TabulationSheet(t5,r5);
        a.display();
        b.display();
        c.display();
    }
}

        

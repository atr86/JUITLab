// Implement a class for a “Person”. Person has data members ‘age’, ’weight’, ‘height’,
// ‘dateOfBirth’, ‘address’ with proper reader/write methods etc. Now create two subclasses
// “Employee” and “Student”. Employee will have additional data member ‘salary’,
// ‘dateOfJoining’, ‘experience’ etc. Student has data members ‘roll’, ‘listOfSubjects’, their marks
// and methods ‘calculateGrade’. Again create two sub-classes “Technician” and “Professor” from
// Employee. Professor has data members ‘courses’, ‘listOfAdvisee’ and their add/remove
// methods. Write a main() function to demonstrate the creation of objects of different classes and
// their method calls.

class Person{
    protected  int age;
    protected  int height;
    protected  int weight;
    protected  int dob;
    protected  String address;
    
    // Person(int a, int h, int w, int dob, String ad)
    // {
    //     age=a;
    //     height=h;
    //     weight=w;
    //     this.dob=dob;
    //     address=ad;
    // }
    
    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public int getDob() {
        return dob;
    }

    public void setDob(int dob) {
        this.dob = dob;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    void display()
    {
        System.out.println("Age = "+age);
        System.out.println("Height = "+height);
        System.out.println("Weight = "+weight);
        System.out.println("Date of Birth = "+dob);
        System.out.println("Stays in = "+address);
    }
}
class Employee extends Person
{

    protected  int doj;
    protected  int salary;
    protected  int exp;

Employee()
{
    super();
}

public int getDoj() {
    return doj;
}

public void setDoj(int doj) {
    this.doj = doj;
}

public int getSalary() {
    return salary;
}

public void setSalary(int salary) {
    this.salary = salary;
}

public int getExp() {
    return exp;
}

public void setExp(int exp)
{
    this.exp = exp;
}

void display()
{
    super.display();
    System.out.println("Has "+ getExp()+" years of experience, joined this company in "+getDoj()+" and earns "+getSalary());
}

}


class Student extends Person
{
    protected  int roll;
    protected  int marks[];
    protected  String sub[];
    protected  int calcgrade;
    public int getRoll() {
        return roll;
    }
    public void setRoll(int roll) {
        this.roll = roll;
    }
    public int[] getMarks() {
        return marks;
    }
    public void setMarks(int[] marks) {
        this.marks = marks;
    }
    public String[] getSub() {
        return sub;
    }
    public void setSub(String[] sub) {
        this.sub = sub;
    }
    public int getCalcgrade() {
        return calcgrade;
    }
    public void setCalcgrade(int calcgrade) {
        this.calcgrade = calcgrade;
    }
    void display()
    {
        super.display();
        System.out.println("Student Has roll no "+roll);
        int i,total=0;
        for(i=0;i<marks.length;i++)
        {
            System.out.println("Obtained in "+ sub[i]+" - "+marks[i]);
            total+=marks[i];
        }
        calcgrade=(int)(total/100.0*10.0);
        System.out.println("His grade point average is "+getCalcgrade());
    }
}

class Technician extends Employee
{
    protected  String skill[];

public String[] getSkill() {
    return skill;
}

public void setSkill(String[] skill) {
    this.skill = skill;
}
   void display()
   {
    super.display();
    System.out.println("Has the following skill set");
    int i;
    for(i=0;i<skill.length;i++)
    {
        System.out.print(skill[i]);
    }
    System.out.println();
   }
}

class Professor extends Employee
{
    protected  String course[];
    protected  String liad[];
    public String[] getCourse() {
        return course;
    }
    public void setCourse(String[] course) {
        this.course = course;
    }
    public String[] getLiad() {
        return liad;
    }
    public void setLiad(String[] liad) {
        this.liad = liad;
    }
    void display()
    {
        super.display();
        System.out.println("Professor teaches following courses ");
        int i;
        for(i=0;i<course.length;i++)
        {
            System.out.println(course[i]);
        }
        System.out.println("List of Advisors");
        for(i=0;i<liad.length;i++)
        {
            System.out.println(liad[i]);
        }
    }
}


public class q9
{
    public static void main(String args[])
    {
        Person p= new Person();
        Employee e= new Employee();
        Student s= new Student();
        Technician t= new Technician();
        Professor pr= new Professor();
        p.setAddress("Behala");
        p.setAge(37);
        p.setDob(12112000);
        p.setHeight(60);
        p.setWeight(70);
        e.setAddress("Behala");
        e.setAge(37);
        e.setDob(12112000);
        e.setHeight(60);
        e.setWeight(70);
        e.setDoj(22052024);
        e.setExp(3);
        e.setSalary(12);
        t.setAddress("Behala");
        t.setAge(37);
        t.setDob(12112000);
        t.setHeight(60);
        t.setWeight(70);
        t.setDoj(22052024);
        t.setExp(3);
        t.setSalary(8);
        String skl[]={"Msoffice","Linux"};
        t.setSkill(skl);
        pr.setAddress("Behala");
        pr.setAge(37);
        pr.setDob(12112000);
        pr.setHeight(60);
        pr.setWeight(70);
        pr.setDoj(22052024);
        pr.setExp(3);
        pr.setSalary(11);
        String ad[]={"Ram","Shyam","Jadu","Madhu"};
        String cr[]={"ML","Bioinformatics"};
        pr.setLiad(ad);
        pr.setCourse(cr);
        s.setAddress("Behala");
        s.setAge(37);
        s.setDob(12112003);
        s.setHeight(60);
        s.setWeight(70);
        s.setRoll(86);
        int m[]={78,89,83,85,73};
        String sub[]={"P","C","M","CS","Eng"};
        s.setMarks(m);
        s.setSub(sub);
        System.out.println("Person:-");
        p.display();
        System.out.println("\nEmployee:-");
        e.display();
        System.out.println("\nStudent:-");
        s.display();
        System.out.println("\nTechnician:-");
        t.display();
        System.out.println("\nProfessor:-");
        pr.display();

        
        
    }
}

class student
{
	String name;
	int a;
	int b;
	int c;
	student()
{
	name="";
	a=b=c=0;
}
	void get(String n, int m1, int m2, int m3)
		{
			name=n;
			a=m1;
			b=m2;
			c=m3;
		}
	double avg()
{
return (a+b+c)/3.0;
}

void display()
{
System.out.println("Name is "+ name+"\nTotal Marks is="+(a+b+c));
}
public static void main(String args[])
{
	student s= new student(); 
        s.get("Atrij Roy",92, 85, 88);
	s.display();
	System.out.println("The Avg of 3 subjects="+s.avg());
}
}	

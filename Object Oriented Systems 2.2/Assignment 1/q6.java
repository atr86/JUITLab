// 6. Write a Java class “Employee” containing information name, id, address, salary etc. Write
// necessary constructor and read/write methods.
// Create a class “Dept” that has a name, location etc. The “Dept” contains a number of
// “Employee”. Write methods “add” and “remove” to add and remove an employee to/from this
// department.
// Write a main() function and create “Information Technology” department. Add five employees
// and print yearly expenditure for this department.

class Employee
{
	private String name;
	private int id;
	private String address;
	private double sal;
	Employee(String n, int id, String a, double sal)
	{
		name=n;
		this.id=id;
		address=a;
		this.sal=sal;
	}
	double get_sal()
	{
		return sal;
	}
	int get_id()
	{
		return id;
	}
	String get_name()
	{
		return(name);
	}
	String get_add()
	{
		return (address);
	}
}

class Dept 
{
	Employee e[];
	int top;
	String name;
	String loc;

	Dept(String n, String l,int max)
{
	e= new Employee[max];
	top=-1;
	n=name;
	loc=l;
		}

	void create(String n, int id, String a, double sal)
	{	
		if(top==e.length-1)
		return;
		top++;
		e[top]=new Employee(n, id, a, sal);
	}
	void delete(int id)
	{
		if(top==-1)
			System.out.println("No elements added till now");
		int i,j ;
		for(i=0;i<=top;i++)
		{
			if(e[i].get_id()==id)
			{
				for(j=i;j<top;j++)
				{
					e[j]=e[j+1];
				}
			break;
			}
		}
		top--;
	}
}

public class q6 {
	public static void main(String args[])
	{
		Dept d= new Dept("Information Technology","Saltlake",10);
		d.create("Atrij Roy",1,"Chingrighata",10000);
		d.create("Anumit Kr Jana",2,"Chingrighata",10000);
		d.create("Abishkar Chatterjee",3,"Chingrighata",10000);
		d.create("Asmit Deb",4,"Chingrighata",10000);
		d.create("Arya Sammaddar",5,"Chingrighata",10000);
		int i;
		double total=0.0;
		for(i=0;i<=d.top;i++)
		{
			System.out.println(d.e[i].get_name()+" lives at "+d.e[i].get_add()+" earns "+d.e[i].get_sal());
		}

		for(i=0;i<=d.top;i++)
		{
			total+=d.e[i].get_sal();
		}
        System.out.println("Total expenditure by department is "+ total);
	}

}


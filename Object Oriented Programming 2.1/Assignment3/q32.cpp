// 32.Write a class Employee having data member name, salary etc. Write proper constructors, methods to
// get/set them and a virtual method printDetails() that prints all information of a person. Now write two
// classes Manager and Clerk from Employee. Add ‘type’ and ‘allowance’ in the manager and Clerk
// respectively. Write constructors, methods to get/set them and a override printDetails(). Now create a
// Manager and a Clerk object and call printDetails() function on them to display their information.
// Now Create an array of pointers to Employee and store addresses of two Employee, two Managers and
// two Clerks. Call printDetails() on all elements (a loop may be used). Also find the total salary drawn
// by all employees.
#include <string>
#include <iostream>
using namespace std;
class Employee
{
	string name;
	float salary;
	public:
		Employee(string s, float f)
{
			name=s;
			salary=f;
			
}
void set(string s, float f)
{
		name=s;
		salary=f;

}
float getSal()
{
	return salary;
}
string getName()
{
	return name;
}
virtual void printDetails();

};
void Employee::printDetails()// no need to write virtual here
{
	cout<<"Name is "<<name<<endl<<"Salary is "<<salary<<endl<<endl;
}

class Manager:public Employee
{
string type;
float allowance;
public:
		Manager(string n, string t, float sal, float a):Employee(n,sal)
{
	type=t;
	allowance=a;
}
string getType()
{
	return type;
}
float getAllow()
{
	return allowance;
}
void set(string t, float a)
{
	type=t;
	allowance=a;
}
void printDetails()
{
	cout<<"Employee is a "<<type<<" Manager "<<endl;
	Employee::printDetails();
	cout<<"Allowance is "<<allowance<<endl;
	cout<<"Total salary is "<<(getSal()+allowance)<<endl<<endl;

}
};
class Clerk:public Employee
{
string type;
float allowance;
public:
		Clerk(string n, string t, float sal, float a):Employee(n,sal)
{
	type=t;
	allowance=a;
}
string getType()
{
	return type;
}
float getAllow()
{
	return allowance;
}
void set(string t, float a)
{
	type=t;
	allowance=a;
}
void printDetails()
{
	cout<<"Employee is a "<<type<<" Department Clerk "<<endl;
	Employee::printDetails();
	cout<<"Allowance is "<<allowance<<endl;
	cout<<"Total salary is "<<(getSal()+allowance)<<endl<<endl;
	
}
};

int main()
{
	Clerk c("Ram","Salary",35000,10000);
	Manager m("Shyam","Project",35000,10000);
	c.printDetails();
	m.printDetails();
	Employee* e[6];
	int i;
	e[0]=new Employee("Jodu", 45000);
	e[1]=new Employee("Madhu",58000);
	e[2]=new Manager("Rahim", "Execution", 35000, 10000);
	e[3]=new Manager("Farhan", "Hiring", 30000, 8000);
	e[4]=new Clerk("Abhi","Accounting", 40000,9000 );
	e[5]=new Clerk("Nitin","Law", 40000,9000 );
	
	
	for(i=0;i<6;i++)
		{
			e[i]->printDetails();
		}
}
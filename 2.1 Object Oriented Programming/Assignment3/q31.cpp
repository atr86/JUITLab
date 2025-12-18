// Online C++ compiler to run C++ program online
#include <iostream>
using namespace std;

class Person
{
    int age;
    int dob;
    string name;
    public:
    Person()
    {}
    void set(string s)
    {
        name=s;
    }
    void set(int dob)
   {
        this->dob=dob;
        age= 2024-(dob%10000);
    }
    string get_name()
    {
        return name;
    }
    int get_age()
    {
        return age;
    }
    int get_dob()
    {
        return dob;
    }
    virtual void printDetails()
    {
        cout<<"Name"<<name<<endl;
        cout<<"DOB"<<dob<<endl;
        cout<<"AGE"<<age<<endl;
    }
};

class Student:public Person
{
    int roll,yoa;
    string instname;
    public:
    Student()
                {yoa=2023;
                roll=20230001;
                instname="Jadavpur University";}
    void set_YOA(int date=2023)

    {
        yoa=date;
    }
    void set_instname(string s="Jadavpur University")
    {
        instname=s;
    }
    void set_roll(int r=20230001)
    {
        roll=r;
    }
    string get_instname()
    {
        return instname;
    }
    
    int get_roll()
    {
        return roll;
    }
    int get_YOA()
    {
        return yoa;
    }
    void printDetails()
    {
        //Person::printDetails();
        
        cout<<"InstituteName"<<instname<<endl;
        cout<<"RollNo"<<roll<<endl;
        cout<<"Year of Admission"<<yoa<<endl;
    }
};

int main()
{
    cout<<"Person Details"<<endl;
    Person p;
    p.set("Atrij");
    p.set(11122004);
    p.printDetails();
    cout<<"Student Details"<<endl;
    Student s;
    s.set("Atrij");
    s.set(11122004);
    s.set_roll(23151098);
    s.set_YOA(2022);
    s.set_instname("Jadavpur University");
    s.printDetails();
    Person *per[4];
    per[0]=new Person();
    
    per[1]=new Person();

    per[2]=new Student();
    per[3]=new Student();
    per[0]->set("Ronojoy");
    per[0]->set(11122005);
    
    per[01]->set("Sanjoy");
    per[01]->set(11122005);
    
    per[2]->set("Monojoy");
    per[2]->set(12082006);
    
    per[3]->set("Joy");
    per[3]->set(12092006);
    
    int i;
    for(i=0;i<4;i++)
        {
            per[i]->printDetails();
        }
}

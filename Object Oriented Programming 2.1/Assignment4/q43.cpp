#include <iostream>
using namespace std;

/*Design and implement class(es) to support the following code segment.
Index in(4), out(10);
int x = in;
int y = in + out;
in = 2;
Integer i;
i = in;*/

class Index
{
	int i;
	public:
	Index(int ind=0)
	{
	    i=ind;
	}
	int operator+(Index ind)
	{
	    return i+ind.i;
	}
	operator int()
	{
	    return i;
	}
	int get_i()
	{
		return i;
	}
};

class Integer
{

    int i;
    public:
    Integer(int i=0)
    {
        this->i=i;
    }
    void operator=(Index ind)
    {
    	this->i=ind.get_i();
    }
    int get_i()
	{
		return i;
	}
    
};

int main()
{
    Index in(4), out(10);
    int x = in;
    cout<<x;
    int y = in + out;
    cout<<y;
    in = 2;
    cout<<in.get_i();
    Integer i;
    i  = in;
    cout<<i.get_i();
}


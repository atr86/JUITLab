class Base1
{
int b1;
public:
Base1(int b=0)
{
b1=b;
}
};
class Base2
{
int b2;
public:
Base2(int b=0)
{
b2=b;
}
};
class Derived:public Base1, public Base2
{
int d;
public:
Derived()
{
}
};


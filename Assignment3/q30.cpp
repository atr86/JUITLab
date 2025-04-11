#include <iostream>
class A{};
class B{};
class C{};
class D:public A,public B{};
class E:public B,public C{};
class F:public D,public E{};



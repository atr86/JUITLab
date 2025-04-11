#include <iostream>
using namespace std;
class flow {
public:
  flow() { cout << "You have created an exception "; }
  void over() { cout << "An overflow! \n"; }
  void under() { cout << "An Underflow!\n"; }
};
class Stack {
  int *buffer, top, size;

public:
  Stack(int);
  void push(int);
  int pop();
  void disp();
};
Stack ::Stack(int n) {
  buffer = (int *)malloc(n * sizeof(int));
  top = -1;
  size = n;
}
void Stack ::push(int p) {
  if (top == size - 1)
    throw flow();
  top++;
  *(buffer + top) = p;
}
int Stack ::pop() {
  if (top == -1)
    throw flow();
  else {
    top--;
    return *(buffer + top+1);
  }
}
void Stack ::disp() {
  int i;
  for (i = 0; i <= top; i++) {
    cout << *(buffer + i) << endl;
  }
}
int main() {
  Stack s(5);
  cout << "Pushed in 1 2 3 4 5 6" << endl;
  try {
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    s.push(6);
  } catch (flow o) {
    o.over();
  }
  s.disp();
  try {
    cout << "Popped out " << s.pop() << " " << s.pop() <<" "<< s.pop() << " "
         << s.pop() << " " << s.pop() << " " << s.pop() << " " << endl;
  } catch (flow o) {
    o.under();
  }
  s.disp();
}

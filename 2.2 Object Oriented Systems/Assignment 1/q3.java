class Stack
{
	int arr[];
	int size;
	int top;
	Stack(int n)
	{
		top=-1;
		size=n;
		arr= new int[n];
	}
	void push(int x)
	{
		if(top==size-1)
			System.out.println("Overflow!");
		else{
			top++;
			arr[top]=x;
		}
         }

	int pop()
	{
		if (top==-1)
			return -9999;
		else
			{
				top--;
				return arr[top+1];
			}
	}
	void print()
	{
		int i;
		for(i=top;i>=0;i--)
		{
			System.out.println(arr[i]);
		}
	}
}

class q3
{
	public static void main()
	{
		Stack st= new Stack(10);
		System.out.println("Entering 1 to 11 in a stack of max size 10");
		int i;
		for(i=0;i<10;i++)
		{
			System.out.println("Pushing"+ i);
			st.push(i);
		System.out.println("Stack Condition");
		st.print();
		}
		System.out.println("Popping from stack 11 times");
		for(i=0;i<11;i++)
		{
			System.out.println("Popped out "+st.pop());
			System.out.println("Stack condition now");
			st.print();
		}
	}
	public static void main(String args[])
	{
		Stack st = new Stack(30);
		st.push(10);
		st.push(20);
		st.push(30);
		st.push(15);
		st.push(9);
		System.out.println("The Stack is");
		st.print();
		System.out.println("Pop 3 times"+st.pop()+" "+st.pop()+" "+st.pop());
		st.print();
		System.out.println("Popping again"+st.pop());
	}
}



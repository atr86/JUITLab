class Room
{
	int l;
	int b;
	int h;
	Room(int l, int b, int h)
	{
		this.l=l;
		this.b=b;
		this.h=h;
		 System.out.println("Dimensions are"+l+"*"+b+"*"+h);
	}
	Room()
	{
		l=1;
		b=1;
		h=1;
		System.out.println("Dimensions are 1*1*1");
	}
	int vol()
	{
		return l*b*h;
	}
}

class RoomDemo
{
	public static void main(String args[])
	{	
		Room r2= new Room();
		System.out.println("Volume of Room with default constructor "+r2.vol());
		Room r1= new Room(1,2,3);
		System.out.println("Volume of Room with param constructor "+r1.vol());
	}
}



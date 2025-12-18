class ChildThread extends Thread
{
	public void run()
	{
		System.out.println("I am in "+ getName()+ " which started at"+ System.currentTimeMillis());
	}

}

public class MainThread
{
	public static void main(String[] args)
	{
		Thread t= Thread.currentThread();
		ChildThread ct= new ChildThread();
		ct.setName("child");
                //ct.setPriority(6);
        ct.start();
		System.out.println("I am in Main Thread, which started at"+ System.currentTimeMillis());
		//System.out.println("I am in "+t.getName()+" thread with priority "+ t.getPriority());
	}
}
			

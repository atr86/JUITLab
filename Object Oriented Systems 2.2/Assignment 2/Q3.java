class Factorial extends Thread
{
    public static final Object lock = new Object();
    static int turn = 1;
    int[] buf;
    public Factorial(int[] a)
    {
        buf = a;
        start();
    }
    public void run()
    {
        int p = 1;
        while(turn<=10)
        {
            synchronized(lock)
            {
                p = p*turn;
                buf[0] = p;
                turn++;
                lock.notify();
                try{
                    lock.wait();
                }
                catch(Exception e)
                {
                 e.printStackTrace();
                }
            }
        }
    }
    public static void main(String args[]) throws Exception{
        int[] a = new int[1];
        Factorial f = new Factorial(a);
        double s = 0;
        while(turn<=10){
        synchronized(lock)
        {
            try{
                lock.wait();
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
            System.out.println("Term " + (turn-1) + ": 1/" + a[0]);
            s+=1.0/a[0];
            lock.notify();
        }
        }
        f.join();
        System.out.println("\nSum is = " + s);
    }
}
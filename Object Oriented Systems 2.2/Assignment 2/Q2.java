public class Q2 extends Thread {
    static int turn = 1; 
    static final Object lock = new Object();
    int cas;

    public Q2(int c) {
        cas = c;
        start();
    }

    public void run() {
        while (turn <= 8) {
            synchronized (lock) {
                while (turn % 2 == 0) {
                    try {
                        lock.wait(); 
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                if(turn<=8)
                System.out.print(turn + " ");
                if(cas==2){
                    turn++; 
                    lock.notify();
                }
                else
                    turn= turn+2;
            }
        }
        System.out.println();
    }

    public static void main(String args[]) throws Exception {
        Q2 ob1 = new Q2(1);
        ob1.join();
        turn=2;
        while(turn<=8)
        {
            System.out.print(turn + " ");
            turn = turn+2;
        }
        turn=1;
        System.out.println();
        Q2 ob2 = new Q2(2);
        while (turn <= 8) {
            synchronized (lock) {
                while (turn % 2 != 0) {
                    try {
                        lock.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                
                System.out.print(turn + " ");
                turn++; 
                lock.notify();
            }
        }
    }
}

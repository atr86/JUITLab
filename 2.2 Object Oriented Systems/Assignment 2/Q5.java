class Series extends Thread {
    static int n = 1; 
    static final Object lock = new Object();
    static int sum = 0;

    public Series() {
        start();
    }

    public void run() {
        while (n <= 100) {
            synchronized (lock) {
                while (n % 2 == 0) {
                    try {
                        lock.wait(); 
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                if(n<=99)
                    sum += n;
                n++; 
                lock.notify();
            }
        }
    }

    public static void main(String args[]) throws Exception {
        Series ob = new Series();
        while (n <= 100) {
            synchronized (lock) {
                while (n % 2 != 0) {
                    try {
                        lock.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                if(n<=100)
                    sum += n;
                n++; 
                lock.notify();
            }
        }
        System.out.println("Sum from 1 to 100 in two threads is = " + sum);
    }
}

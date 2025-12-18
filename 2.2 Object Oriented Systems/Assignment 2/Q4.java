import java.io.*;

class FileReader extends Thread {
    public static final Object lock = new Object();
    int[] buf;
    static boolean end = false;

    public FileReader(int[] a) {
        buf = a;
        start();
    }

    public void run() {
        String fileName = "numbers.txt";
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(fileName)))) {
            String line;
            while ((line = br.readLine()) != null) {
                synchronized (lock) {
                    try {
                        int number = Integer.parseInt(line.trim());
                        buf[0] = number;
                        lock.notify();  
                        lock.wait();    
                    } catch (Exception e) {
                        System.out.println("Skipping invalid entry");
                    }
                }
            }
         
            synchronized (lock) {
                end = true;
                lock.notify();
            }
        } catch (Exception e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }

    public static void main(String[] args) throws Exception {
        int[] a = new int[1];
        FileReader ob = new FileReader(a);
        int sum = 0;

        while (!end) {
            synchronized (lock) {
                lock.wait(); 
                if (end) break;  
                sum += a[0];  
                lock.notify();  
            }
        }

        ob.join(); 
        System.out.println("\nSum = " + sum);  
    }
}

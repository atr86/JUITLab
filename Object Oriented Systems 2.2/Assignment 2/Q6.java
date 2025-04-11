import java.io.*;
import java.util.Scanner;
class BinarySearch extends Thread
{
    int i;
    int j;
    int[] arr;
    int k;
    static int e;
    static boolean found = false;
    public BinarySearch(int[] a, int i, int j,int e, int k)
    {
        arr = a;
        this.i = i;
        this.j = j;
        this.e = e;
        this.k = k;
        start();
    }
    public void run()
    {
        while(i<j && found==false)
        {

                int mid = (i+j)/2;
                if(e>arr[mid])
                    i = mid+1;
                else if(e<arr[mid])
                    j = mid-1;
                else    
                {
                    System.out.println("ELEMENT " + e + " FOUND in Thread t"+k+" at index " + mid +"!");
                    found = true;
                }
        }
        if(found==false)
            System.out.println("Cannot find element " + e + " in Thread t"+k);
    }
    public static void main(String[] args)
    {
        System.out.println("Enter number of elements n in array, make it so that n mod 10 = 0");
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        System.out.println("Enter elements in the array");
        int a[] = new int[n];
        for(int i = 0; i<n; i++)
        {
            a[i] = sc.nextInt();
        }
        System.out.println("Enter element to search");
        int e = sc.nextInt();
        BinarySearch[] bs = new BinarySearch[n/10];
        int count = 0;
        for(int i = 0; i<n; i=i+10)
        {
            bs[count++] = new BinarySearch(a, i, i+10, e, count);
        }
    }

}
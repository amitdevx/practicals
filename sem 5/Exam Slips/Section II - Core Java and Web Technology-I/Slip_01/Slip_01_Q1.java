import java.util.Scanner;

public class Slip_01_Q1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter size of array: ");
        int n = sc.hasNextInt() ? sc.nextInt() : 5;
        int[] arr = new int[n];
        int sum = 0;

        System.out.println("Enter " + n + " elements:");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.hasNextInt() ? sc.nextInt() : (i + 1) * 10;
            sum += arr[i];
        }

        System.out.print("Array Elements: ");
        for (int x : arr) {
            System.out.print(x + " ");
        }
        System.out.println("\nSum of Elements: " + sum);
        sc.close();
    }
}

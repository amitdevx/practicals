import java.util.Scanner;
import java.util.Arrays;

public class Slip_01_Q1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter size of array: ");
        int n = sc.nextInt();
        int[] arr = new int[n];
        int sum = 0;

        System.out.println("Enter " + n + " elements:");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
            sum += arr[i];
        }

        Arrays.sort(arr);

        System.out.print("Array Elements in ascending order: ");
        for (int x : arr) {
            System.out.print(x + " ");
        }
        System.out.println("\nSum of Elements: " + sum);
        sc.close();
    }
}

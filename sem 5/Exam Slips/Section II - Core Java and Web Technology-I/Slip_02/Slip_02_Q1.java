import java.util.Scanner;

public class Slip_02_Q1 {
    public static boolean isArmstrong(int num) {
        int original = num, sum = 0, digits = 0;
        int temp = num;
        while (temp > 0) {
            digits++;
            temp /= 10;
        }
        temp = num;
        while (temp > 0) {
            int rem = temp % 10;
            sum += Math.pow(rem, digits);
            temp /= 10;
        }
        return sum == original;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter start of range: ");
        int start = sc.hasNextInt() ? sc.nextInt() : 1;
        System.out.print("Enter end of range: ");
        int end = sc.hasNextInt() ? sc.nextInt() : 500;

        System.out.println("Armstrong numbers between " + start + " and " + end + ":");
        for (int i = start; i <= end; i++) {
            if (isArmstrong(i)) {
                System.out.print(i + " ");
            }
        }
        System.out.println();
        sc.close();
    }
}

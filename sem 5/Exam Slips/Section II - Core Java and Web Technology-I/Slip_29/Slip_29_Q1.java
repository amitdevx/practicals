import java.util.Scanner;

class ZeroNumberException extends Exception {
    public ZeroNumberException(String msg) {
        super(msg);
    }
}

public class Slip_29_Q1 {
    public static boolean isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    public static void checkNumber(int n) throws ZeroNumberException {
        if (n == 0) {
            throw new ZeroNumberException("Number is 0");
        }
        if (isPrime(n)) {
            System.out.println(n + " is a Prime Number.");
        } else {
            System.out.println(n + " is NOT a Prime Number.");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a number: ");
        if (scanner.hasNextInt()) {
            int num = scanner.nextInt();
            try {
                checkNumber(num);
            } catch (ZeroNumberException e) {
                System.out.println("Exception: " + e.getMessage());
            }
        }
    }
}

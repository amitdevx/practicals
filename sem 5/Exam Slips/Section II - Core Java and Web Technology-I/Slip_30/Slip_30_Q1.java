class MyNumber {
    private int value;

    public MyNumber() {
        this.value = 0;
    }

    public MyNumber(int val) {
        this.value = val;
    }

    public boolean isNegative() { return value < 0; }
    public boolean isPositive() { return value > 0; }
    public boolean isOdd() { return value % 2 != 0; }
    public boolean isEven() { return value % 2 == 0; }

    public void displayProperties() {
        System.out.println("Number: " + value);
        System.out.println("isPositive: " + isPositive());
        System.out.println("isNegative: " + isNegative());
        System.out.println("isEven:     " + isEven());
        System.out.println("isOdd:      " + isOdd());
    }

    public static void main(String[] args) {
        int inputVal = (args.length > 0) ? Integer.parseInt(args[0]) : 25;
        MyNumber obj = new MyNumber(inputVal);
        obj.displayProperties();
    }
}

public class Slip_30_Q1 {
    public static void main(String[] args) {
        MyNumber.main(args);
    }
}

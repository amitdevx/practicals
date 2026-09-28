interface Calculator {
    double add(double a, double b);
    double subtract(double a, double b);
}

class SimpleCalc implements Calculator {
    public double add(double a, double b) {
        return a + b;
    }

    public double subtract(double a, double b) {
        return a - b;
    }
}

public class Slip_25_Q1 {
    public static void main(String[] args) {
        SimpleCalc calc = new SimpleCalc();
        double x = 45.5, y = 12.3;

        System.out.println("Calculator Interface Implementation:");
        System.out.println(x + " + " + y + " = " + calc.add(x, y));
        System.out.println(x + " - " + y + " = " + calc.subtract(x, y));
    }
}

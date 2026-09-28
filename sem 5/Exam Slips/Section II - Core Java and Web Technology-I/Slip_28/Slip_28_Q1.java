class InvalidDateException extends Exception {
    public InvalidDateException(String msg) {
        super(msg);
    }
}

class MyDate {
    int day, month, year;

    public MyDate(int day, int month, int year) throws InvalidDateException {
        if (!isValid(day, month, year)) {
            throw new InvalidDateException("Invalid Date: " + day + "/" + month + "/" + year);
        }
        this.day = day;
        this.month = month;
        this.year = year;
    }

    private boolean isValid(int d, int m, int y) {
        if (y < 1 || m < 1 || m > 12 || d < 1) return false;
        int[] daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        // Leap year
        if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0)) {
            daysInMonth[1] = 29;
        }
        return d <= daysInMonth[m - 1];
    }

    public void display() {
        System.out.printf("Date: %02d/%02d/%04d\n", day, month, year);
    }

    public static void main(String[] args) {
        try {
            MyDate d1 = new MyDate(25, 9, 2026);
            d1.display();
        } catch (InvalidDateException e) {
            System.out.println("Exception: " + e.getMessage());
        }

        try {
            MyDate d2 = new MyDate(31, 2, 2026);
            d2.display();
        } catch (InvalidDateException e) {
            System.out.println("Exception caught: " + e.getMessage());
        }
    }
}

public class Slip_28_Q1 {
    public static void main(String[] args) {
        MyDate.main(args);
    }
}

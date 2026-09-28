# Java Templates for CS-306 Slips 21 to 30

def get_java_slip21_q1():
    return '''class College {
    int cno;
    String cname;
    String caddr;

    public College(int cno, String cname, String caddr) {
        this.cno = cno;
        this.cname = cname;
        this.caddr = caddr;
    }
}

class Department extends College {
    int dno;
    String dname;

    public Department(int cno, String cname, String caddr, int dno, String dname) {
        super(cno, cname, caddr);
        this.dno = dno;
        this.dname = dname;
    }

    public void display() {
        System.out.println("College No:   " + cno);
        System.out.println("College Name: " + cname);
        System.out.println("Address:      " + caddr);
        System.out.println("Dept No:      " + dno);
        System.out.println("Dept Name:    " + dname);
    }
}

public class CollegeDepartmentDemo {
    public static void main(String[] args) {
        Department dept = new Department(101, "Modern College", "Shivajinagar, Pune", 1, "Computer Science");
        System.out.println("--- College & Department Details ---");
        dept.display();
    }
}
'''

def get_java_slip22_q1():
    return '''interface ItemInterface {
    void display();
}

class Product implements ItemInterface {
    static int count = 0;
    int product_id;
    String product_name;
    double product_cost;
    int product_quantity;

    public Product() {
        this.product_id = 0;
        this.product_name = "Sample Product";
        this.product_cost = 0.0;
        this.product_quantity = 0;
        count++;
    }

    public Product(int id, String name, double cost, int qty) {
        this.product_id = id;
        this.product_name = name;
        this.product_cost = cost;
        this.product_quantity = qty;
        count++;
    }

    public void display() {
        System.out.println("ID: " + product_id + "\\tName: " + product_name +
                           "\\tCost: ₹" + product_cost + "\\tQuantity: " + product_quantity);
    }

    public static void showCount() {
        System.out.println("Total Product Objects Created: " + count);
    }
}

public class ProductDemo {
    public static void main(String[] args) {
        Product p1 = new Product(101, "Laptop", 65000, 5);
        Product p2 = new Product(102, "Mouse", 800, 20);
        Product p3 = new Product();

        p1.display();
        p2.display();
        p3.display();

        Product.showCount();
    }
}
'''

def get_java_slip23_q1():
    return '''class Continent {
    String continentName;
    public Continent(String cname) {
        this.continentName = cname;
    }
}

class Country extends Continent {
    String countryName;
    public Country(String cname, String country) {
        super(cname);
        this.countryName = country;
    }
}

class State extends Country {
    String stateName;
    String place;

    public State(String cname, String country, String state, String place) {
        super(cname, country);
        this.stateName = state;
        this.place = place;
    }

    public void display() {
        System.out.println("Place:     " + place);
        System.out.println("State:     " + stateName);
        System.out.println("Country:   " + countryName);
        System.out.println("Continent: " + continentName);
    }
}

public class MultilevelInheritanceDemo {
    public static void main(String[] args) {
        State s = new State("Asia", "India", "Maharashtra", "Pune");
        System.out.println("--- Geographical Hierarchy ---");
        s.display();
    }
}
'''

def get_java_slip24_q1():
    return '''abstract class Shape {
    abstract double area();
    abstract double volume();
}

class Cylinder extends Shape {
    double radius;
    double height;

    public Cylinder(double radius, double height) {
        this.radius = radius;
        this.height = height;
    }

    double area() {
        // Surface area = 2 * PI * r * (r + h)
        return 2 * Math.PI * radius * (radius + height);
    }

    double volume() {
        // Volume = PI * r^2 * h
        return Math.PI * radius * radius * height;
    }
}

public class CylinderDemo {
    public static void main(String[] args) {
        Cylinder cyl = new Cylinder(5.0, 10.0);
        System.out.printf("Cylinder (Radius: 5.0, Height: 10.0):\\n");
        System.out.printf("Surface Area: %.2f sq. units\\n", cyl.area());
        System.out.printf("Volume:       %.2f cubic units\\n", cyl.volume());
    }
}
'''

def get_java_slip25_q1():
    return '''interface Calculator {
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

public class InterfaceCalcDemo {
    public static void main(String[] args) {
        SimpleCalc calc = new SimpleCalc();
        double x = 45.5, y = 12.3;

        System.out.println("Calculator Interface Implementation:");
        System.out.println(x + " + " + y + " = " + calc.add(x, y));
        System.out.println(x + " - " + y + " = " + calc.subtract(x, y));
    }
}
'''

def get_java_slip26_q1():
    return '''class NotEligibleForExamException extends Exception {
    public NotEligibleForExamException(String msg) {
        super(msg);
    }
}

class Student {
    String student_name;
    int student_rollno;
    int total_lectures;
    int attended_lectures;

    public Student(String name, int roll, int total, int attended) throws NotEligibleForExamException {
        this.student_name = name;
        this.student_rollno = roll;
        this.total_lectures = total;
        this.attended_lectures = attended;

        double percentage = ((double) attended / total) * 100;
        if (percentage < 75.0) {
            throw new NotEligibleForExamException("Student is Not Eligible for Exam (Attendance: " + String.format("%.1f", percentage) + "%)");
        }
    }

    public void display() {
        System.out.println("Roll No: " + student_rollno + "\\tName: " + student_name + "\\tStatus: Eligible for Exam");
    }
}

public class StudentAttendanceDemo {
    public static void main(String[] args) {
        try {
            Student s1 = new Student("Pooja", 101, 80, 65);
            s1.display();
        } catch (NotEligibleForExamException e) {
            System.out.println("Exception: " + e.getMessage());
        }

        try {
            Student s2 = new Student("Vikas", 102, 80, 50);
            s2.display();
        } catch (NotEligibleForExamException e) {
            System.out.println("Exception caught: " + e.getMessage());
        }
    }
}
'''

def get_java_slip27_q1():
    return '''public class Person {
    private String personname;
    private String aadharno;
    private String panno;

    public Person(String personname, String aadharno, String panno) {
        this.personname = personname;
        this.aadharno = aadharno;
        this.panno = panno;
    }

    public void display() {
        System.out.println("Name: " + this.personname + "\\tAadhar: " + this.aadharno + "\\tPAN: " + this.panno);
    }

    public static void main(String[] args) {
        Person[] people = {
            new Person("Amit Kumar", "1234-5678-9012", "ABCDE1234F"),
            new Person("Sneha Joshi", "2345-6789-0123", "BCDEF2345G"),
            new Person("Rajesh Shinde", "3456-7890-1234", "CDEFG3456H"),
            new Person("Kavita Rao", "4567-8901-2345", "DEFGH4567I"),
            new Person("Nikhil Deshmukh", "5678-9012-3456", "EFGHI5678J")
        };

        System.out.println("--- Person Details (Demonstrating 'this' keyword) ---");
        for (Person p : people) {
            p.display();
        }
    }
}
'''

def get_java_slip28_q1():
    return '''class InvalidDateException extends Exception {
    public InvalidDateException(String msg) {
        super(msg);
    }
}

public class MyDate {
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
        System.out.printf("Date: %02d/%02d/%04d\\n", day, month, year);
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
'''

def get_java_slip29_q1():
    return '''class ZeroNumberException extends Exception {
    public ZeroNumberException(String msg) {
        super(msg);
    }
}

public class PrimeOrZeroCheck {
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
        int[] testNumbers = {17, 0, 24};
        for (int num : testNumbers) {
            try {
                System.out.print("Testing number " + num + ": ");
                checkNumber(num);
            } catch (ZeroNumberException e) {
                System.out.println("Exception: " + e.getMessage());
            }
        }
    }
}
'''

def get_java_slip30_q1():
    return '''public class MyNumber {
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
'''

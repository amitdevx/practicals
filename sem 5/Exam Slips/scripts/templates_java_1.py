# Java Templates for CS-306 Core Java

def get_java_slip01_q1():
    return '''import java.util.Scanner;

public class ArraySum {
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
        System.out.println("\\nSum of Elements: " + sum);
        sc.close();
    }
}
'''

def get_java_slip02_q1():
    return '''import java.util.Scanner;

public class ArmstrongRange {
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
'''

def get_java_slip03_q1():
    return '''// Package StringOp demo
class Con {
    public String concatenate(String s1, String s2) {
        return s1 + s2;
    }
}

class Comp {
    public boolean compare(String s1, String s2) {
        return s1.equals(s2);
    }
}

public class StringOperationsDemo {
    public static void main(String[] args) {
        Con con = new Con();
        Comp comp = new Comp();

        String str1 = "Pune";
        String str2 = "University";

        System.out.println("String 1: " + str1);
        System.out.println("String 2: " + str2);
        System.out.println("Concatenation: " + con.concatenate(str1, str2));
        System.out.println("Comparison (str1 == str2): " + comp.compare(str1, str2));
    }
}
'''

def get_java_slip04_q1():
    return '''import java.util.Scanner;

public class MatrixOperations {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int rows = 2, cols = 2;
        int[][] a = {{1, 2}, {3, 4}};
        int[][] b = {{5, 6}, {7, 8}};
        int choice;

        System.out.println("Matrix A:");
        printMatrix(a);
        System.out.println("Matrix B:");
        printMatrix(b);

        do {
            System.out.println("\\n1. Add Matrices\\n2. Multiply Matrices\\n3. Transpose of Matrix A\\n4. Exit");
            System.out.print("Enter choice: ");
            choice = sc.hasNextInt() ? sc.nextInt() : 4;

            switch (choice) {
                case 1:
                    int[][] sum = new int[rows][cols];
                    for (int i = 0; i < rows; i++)
                        for (int j = 0; j < cols; j++)
                            sum[i][j] = a[i][j] + b[i][j];
                    System.out.println("Sum:");
                    printMatrix(sum);
                    break;
                case 2:
                    int[][] prod = new int[rows][cols];
                    for (int i = 0; i < rows; i++)
                        for (int j = 0; j < cols; j++)
                            for (int k = 0; k < cols; k++)
                                prod[i][j] += a[i][k] * b[k][j];
                    System.out.println("Product:");
                    printMatrix(prod);
                    break;
                case 3:
                    int[][] trans = new int[cols][rows];
                    for (int i = 0; i < rows; i++)
                        for (int j = 0; j < cols; j++)
                            trans[j][i] = a[i][j];
                    System.out.println("Transpose of A:");
                    printMatrix(trans);
                    break;
                case 4:
                    System.out.println("Exiting.");
                    break;
            }
        } while (choice != 4);
        sc.close();
    }

    static void printMatrix(int[][] m) {
        for (int[] row : m) {
            for (int val : row) System.out.print(val + " ");
            System.out.println();
        }
    }
}
'''

def get_java_slip05_q1():
    return '''import java.io.*;
import java.util.Scanner;

public class ReverseFileContent {
    public static void main(String[] args) {
        String filename = "sample.txt";
        // Create demo file if not exists
        try (FileWriter fw = new FileWriter(filename)) {
            fw.write("Hello World from Java File Handling");
        } catch (IOException e) {
            System.out.println("Error writing sample file.");
        }

        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            StringBuilder content = new StringBuilder();
            String line;
            while ((line = br.readLine()) != null) {
                content.append(line).append("\\n");
            }
            System.out.println("Original File Content:\\n" + content);
            System.out.println("Reversed Content:\\n" + content.reverse());
        } catch (IOException e) {
            System.out.println("File error: " + e.getMessage());
        }
    }
}
'''

def get_java_slip06_q1():
    return '''public class Account {
    private String custname;
    private long accno;

    public Account() {
        this.custname = "Default Customer";
        this.accno = 10000001L;
    }

    public Account(String custname, long accno) {
        this.custname = custname;
        this.accno = accno;
    }

    public void display() {
        System.out.println("Customer Name: " + custname + ", Account No: " + accno);
    }

    public static void main(String[] args) {
        Account a1 = new Account();
        Account a2 = new Account("Rahul Sharma", 9876543210L);

        System.out.println("Account 1 (Default Constructor):");
        a1.display();
        System.out.println("\\nAccount 2 (Parameterized Constructor):");
        a2.display();
    }
}
'''

def get_java_slip07_q1():
    return '''public class Driver {
    private String license_no;
    private String name;
    private String address;
    private int age;

    public Driver(String license_no, String name, String address, int age) {
        this.license_no = license_no;
        this.name = name;
        this.address = address;
        this.age = age;
    }

    public void display() {
        System.out.println("Driver Name: " + name);
        System.out.println("License No:  " + license_no);
        System.out.println("Address:     " + address);
        System.out.println("Age:         " + age);
    }

    public static void main(String[] args) {
        Driver d = new Driver("MH12-20230045", "Amit Patil", "Shivajinagar, Pune", 28);
        System.out.println("--- Driver Details ---");
        d.display();
    }
}
'''

def get_java_slip08_q1():
    return '''abstract class Shape {
    int dim1, dim2;

    public Shape(int dim1, int dim2) {
        this.dim1 = dim1;
        this.dim2 = dim2;
    }

    abstract void printArea();
}

class Rectangle extends Shape {
    public Rectangle(int length, int breadth) {
        super(length, breadth);
    }

    void printArea() {
        System.out.println("Area of Rectangle (" + dim1 + " x " + dim2 + "): " + (dim1 * dim2));
    }
}

class Triangle extends Shape {
    public Triangle(int base, int height) {
        super(base, height);
    }

    void printArea() {
        System.out.println("Area of Triangle (0.5 x " + dim1 + " x " + dim2 + "): " + (0.5 * dim1 * dim2));
    }
}

class Circle extends Shape {
    public Circle(int radius) {
        super(radius, 0);
    }

    void printArea() {
        System.out.println("Area of Circle (radius " + dim1 + "): " + (Math.PI * dim1 * dim1));
    }
}

public class ShapeDemo {
    public static void main(String[] args) {
        Shape s1 = new Rectangle(10, 5);
        Shape s2 = new Triangle(8, 4);
        Shape s3 = new Circle(7);

        s1.printArea();
        s2.printArea();
        s3.printArea();
    }
}
'''

def get_java_slip09_q1():
    return '''public class Employee {
    int id;
    String name;
    double salary;

    public Employee(int id, String name, double salary) {
        this.id = id;
        this.name = name;
        this.salary = salary;
    }

    public void display() {
        System.out.println("ID: " + id + "\\tName: " + name + "\\tSalary: " + salary);
    }

    public static void main(String[] args) {
        Employee[] emps = {
            new Employee(101, "Aarav", 55000),
            new Employee(102, "Pooja", 72000),
            new Employee(103, "Rohan", 48000)
        };

        System.out.println("--- Employee Details ---");
        for (Employee e : emps) e.display();
    }
}
'''

def get_java_slip10_q1():
    return '''import java.io.*;

public class FileUppercase {
    public static void main(String[] args) {
        String filename = "abc.txt";
        // Create demo file
        try (FileWriter fw = new FileWriter(filename)) {
            fw.write("Core Java and Web Technology practical examination 2026-2027.");
        } catch (IOException e) {
            System.out.println("File write error.");
        }

        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            System.out.println("Contents of 'abc.txt' in UPPERCASE:");
            while ((line = br.readLine()) != null) {
                System.out.println(line.toUpperCase());
            }
        } catch (IOException e) {
            System.out.println("File read error: " + e.getMessage());
        }
    }
}
'''

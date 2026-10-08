import java.util.Scanner;

class Employee {
    int id;
    String name;
    double salary;

    public Employee(int id, String name, double salary) {
        this.id = id;
        this.name = name;
        this.salary = salary;
    }

    public void display() {
        System.out.println("ID: " + id + "\tName: " + name + "\tSalary: " + salary);
    }
}

public class Slip_09_Q1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of employees: ");
        if (!sc.hasNextInt()) return;
        int n = sc.nextInt();
        
        Employee[] emps = new Employee[n];
        for (int i = 0; i < n; i++) {
            System.out.println("Enter details for employee " + (i + 1) + ":");
            System.out.print("ID: ");
            int id = sc.nextInt();
            sc.nextLine(); // consume newline
            System.out.print("Name: ");
            String name = sc.nextLine();
            System.out.print("Salary: ");
            double salary = sc.nextDouble();
            emps[i] = new Employee(id, name, salary);
        }

        if (n > 0) {
            Employee maxEmp = emps[0];
            for (int i = 1; i < n; i++) {
                if (emps[i].salary > maxEmp.salary) {
                    maxEmp = emps[i];
                }
            }
            
            System.out.println("\nEmployee with maximum salary:");
            maxEmp.display();
        }
        sc.close();
    }
}

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

public class Slip_09_Q1 {
    public static void main(String[] args) {
        Employee.main(args);
    }
}

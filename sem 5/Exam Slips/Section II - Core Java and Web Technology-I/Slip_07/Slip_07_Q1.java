class Driver {
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

public class Slip_07_Q1 {
    public static void main(String[] args) {
        Driver.main(args);
    }
}

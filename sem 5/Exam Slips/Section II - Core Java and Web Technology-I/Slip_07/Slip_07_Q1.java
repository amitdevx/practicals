class InvalidAgeException extends Exception {
    public InvalidAgeException(String message) {
        super(message);
    }
}

class Driver {
    private String license_no;
    private String name;
    private String address;
    private int age;

    public Driver(String license_no, String name, String address, int age) throws InvalidAgeException {
        if (age < 18) {
            throw new InvalidAgeException("Age is below 18 years");
        }
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
}

public class Slip_07_Q1 {
    public static void main(String[] args) {
        try {
            Driver d1 = new Driver("MH12-20230045", "Amit Patil", "Shivajinagar, Pune", 28);
            System.out.println("\nDriver 1 Details\n");
            d1.display();
            
            System.out.println("\nDriver 2 Details\n");
            Driver d2 = new Driver("MH12-20230046", "Rahul", "Pune", 16);
            d2.display();
        } catch (InvalidAgeException e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }
}

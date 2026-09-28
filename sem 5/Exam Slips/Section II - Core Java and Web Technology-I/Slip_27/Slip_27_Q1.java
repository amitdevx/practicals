class Person {
    private String personname;
    private String aadharno;
    private String panno;

    public Person(String personname, String aadharno, String panno) {
        this.personname = personname;
        this.aadharno = aadharno;
        this.panno = panno;
    }

    public void display() {
        System.out.println("Name: " + this.personname + "\tAadhar: " + this.aadharno + "\tPAN: " + this.panno);
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

public class Slip_27_Q1 {
    public static void main(String[] args) {
        Person.main(args);
    }
}

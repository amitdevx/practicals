class Account {
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
        System.out.println("\nAccount 2 (Parameterized Constructor):");
        a2.display();
    }
}

public class Slip_06_Q1 {
    public static void main(String[] args) {
        Account.main(args);
    }
}

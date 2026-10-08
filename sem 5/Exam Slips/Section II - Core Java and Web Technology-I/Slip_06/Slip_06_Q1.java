class Account {
    protected String custname;
    protected long accno;

    public Account() {
        this.custname = "Default Customer";
        this.accno = 10000001L;
    }

    public Account(String custname, long accno) {
        this.custname = custname;
        this.accno = accno;
    }

    public void display() {
        System.out.println("Customer Name: " + custname);
        System.out.println("Account No: " + accno);
    }
}

class SavingAccount extends Account {
    protected double savingbal;
    protected double minbal;

    public SavingAccount(String custname, long accno, double savingbal, double minbal) {
        super(custname, accno);
        this.savingbal = savingbal;
        this.minbal = minbal;
    }
}

class AccountDetail extends SavingAccount {
    private double depositamt;
    private double withdrawalamt;

    public AccountDetail(String custname, long accno, double savingbal, double minbal, double depositamt, double withdrawalamt) {
        super(custname, accno, savingbal, minbal);
        this.depositamt = depositamt;
        this.withdrawalamt = withdrawalamt;
    }

    @Override
    public void display() {
        super.display();
        System.out.println("Saving Balance: " + savingbal);
        System.out.println("Minimum Balance: " + minbal);
        System.out.println("Deposit Amount: " + depositamt);
        System.out.println("Withdrawal Amount: " + withdrawalamt);
    }
}

public class Slip_06_Q1 {
    public static void main(String[] args) {
        AccountDetail ad = new AccountDetail("Rahul Sharma", 9876543210L, 50000.0, 1000.0, 5000.0, 2000.0);
        System.out.println("Customer Details:");
        ad.display();
    }
}

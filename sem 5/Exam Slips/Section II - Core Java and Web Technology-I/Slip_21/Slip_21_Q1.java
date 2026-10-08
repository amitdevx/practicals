class College {
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

public class Slip_21_Q1 {
    public static void main(String[] args) {
        Department dept = new Department(101, "Modern College", "Shivajinagar, Pune", 1, "Computer Science");
        System.out.println("\nCollege & Department Details\n");
        dept.display();
    }
}

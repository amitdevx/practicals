// Package StringOp demo
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

public class Slip_03_Q1 {
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

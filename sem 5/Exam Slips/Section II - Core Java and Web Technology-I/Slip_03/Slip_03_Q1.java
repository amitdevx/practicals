import stringop.Con;
import stringop.Comp;

public class Slip_03_Q1 {
    public static void main(String[] args) {
        Con con = new Con();
        Comp comp = new Comp();

        String str1 = "Pune";
        String str2 = "University";
        String str3 = "Pune";

        System.out.println("String 1: " + str1);
        System.out.println("String 2: " + str2);
        System.out.println("String 3: " + str3);
        System.out.println("Concatenation of String 1 and 2: " + con.concatenate(str1, str2));
        System.out.println("Comparison of String 1 and 2: " + comp.compare(str1, str2));
        System.out.println("Comparison of String 1 and 3: " + comp.compare(str1, str3));
    }
}

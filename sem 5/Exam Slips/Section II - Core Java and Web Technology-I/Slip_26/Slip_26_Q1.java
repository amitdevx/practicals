class NotEligibleForExamException extends Exception {
    public NotEligibleForExamException(String msg) {
        super(msg);
    }
}

class Student {
    String student_name;
    int student_rollno;
    int total_lectures;
    int attended_lectures;

    public Student(String name, int roll, int total, int attended) throws NotEligibleForExamException {
        this.student_name = name;
        this.student_rollno = roll;
        this.total_lectures = total;
        this.attended_lectures = attended;

        double percentage = ((double) attended / total) * 100;
        if (percentage < 75.0) {
            throw new NotEligibleForExamException("Student is Not Eligible for Exam (Attendance: " + String.format("%.1f", percentage) + "%)");
        }
    }

    public void display() {
        System.out.println("Roll No: " + student_rollno + "\tName: " + student_name + "\tStatus: Eligible for Exam");
    }
}

public class Slip_26_Q1 {
    public static void main(String[] args) {
        try {
            Student s1 = new Student("Pooja", 101, 80, 65);
            s1.display();
        } catch (NotEligibleForExamException e) {
            System.out.println("Exception: " + e.getMessage());
        }

        try {
            Student s2 = new Student("Vikas", 102, 80, 50);
            s2.display();
        } catch (NotEligibleForExamException e) {
            System.out.println("Exception caught: " + e.getMessage());
        }
    }
}

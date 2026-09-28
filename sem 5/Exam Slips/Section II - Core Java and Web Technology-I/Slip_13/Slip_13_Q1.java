class Clock {
    int hours, minutes, seconds;

    public Clock(int h, int m, int s) {
        if (isValid(h, m, s)) {
            this.hours = h;
            this.minutes = m;
            this.seconds = s;
        } else {
            System.out.println("Invalid time provided! Setting default 00:00:00.");
            this.hours = 0;
            this.minutes = 0;
            this.seconds = 0;
        }
    }

    public boolean isValid(int h, int m, int s) {
        return (h >= 0 && h < 24) && (m >= 0 && m < 60) && (s >= 0 && s < 60);
    }

    public void displayAMPM() {
        String mode = (hours >= 12) ? "PM" : "AM";
        int h12 = (hours % 12 == 0) ? 12 : (hours % 12);
        System.out.printf("Time: %02d:%02d:%02d %s\n", h12, minutes, seconds, mode);
    }

    public static void main(String[] args) {
        Clock c1 = new Clock(14, 35, 20);
        System.out.print("24-hr Time (14:35:20) in AM/PM mode: ");
        c1.displayAMPM();

        Clock c2 = new Clock(9, 15, 45);
        System.out.print("24-hr Time (09:15:45) in AM/PM mode: ");
        c2.displayAMPM();
    }
}

public class Slip_13_Q1 {
    public static void main(String[] args) {
        Clock.main(args);
    }
}

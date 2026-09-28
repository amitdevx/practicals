abstract class Shape {
    abstract double area();
    abstract double volume();
}

class Cylinder extends Shape {
    double radius;
    double height;

    public Cylinder(double radius, double height) {
        this.radius = radius;
        this.height = height;
    }

    double area() {
        // Surface area = 2 * PI * r * (r + h)
        return 2 * Math.PI * radius * (radius + height);
    }

    double volume() {
        // Volume = PI * r^2 * h
        return Math.PI * radius * radius * height;
    }
}

public class Slip_24_Q1 {
    public static void main(String[] args) {
        Cylinder cyl = new Cylinder(5.0, 10.0);
        System.out.printf("Cylinder (Radius: 5.0, Height: 10.0):\n");
        System.out.printf("Surface Area: %.2f sq. units\n", cyl.area());
        System.out.printf("Volume:       %.2f cubic units\n", cyl.volume());
    }
}

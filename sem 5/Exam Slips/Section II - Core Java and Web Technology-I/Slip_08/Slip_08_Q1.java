abstract class Shape {
    int dim1, dim2;

    public Shape(int dim1, int dim2) {
        this.dim1 = dim1;
        this.dim2 = dim2;
    }

    abstract void printArea();
}

class Rectangle extends Shape {
    public Rectangle(int length, int breadth) {
        super(length, breadth);
    }

    void printArea() {
        System.out.println("Area of Rectangle (" + dim1 + " x " + dim2 + "): " + (dim1 * dim2));
    }
}

class Triangle extends Shape {
    public Triangle(int base, int height) {
        super(base, height);
    }

    void printArea() {
        System.out.println("Area of Triangle (0.5 x " + dim1 + " x " + dim2 + "): " + (0.5 * dim1 * dim2));
    }
}

class Circle extends Shape {
    public Circle(int radius) {
        super(radius, 0);
    }

    void printArea() {
        System.out.println("Area of Circle (radius " + dim1 + "): " + (Math.PI * dim1 * dim1));
    }
}

public class Slip_08_Q1 {
    public static void main(String[] args) {
        Shape s1 = new Rectangle(10, 5);
        Shape s2 = new Triangle(8, 4);
        Shape s3 = new Circle(7);

        s1.printArea();
        s2.printArea();
        s3.printArea();
    }
}

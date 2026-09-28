interface ItemInterface {
    void display();
}

class Product implements ItemInterface {
    static int count = 0;
    int product_id;
    String product_name;
    double product_cost;
    int product_quantity;

    public Product() {
        this.product_id = 0;
        this.product_name = "Sample Product";
        this.product_cost = 0.0;
        this.product_quantity = 0;
        count++;
    }

    public Product(int id, String name, double cost, int qty) {
        this.product_id = id;
        this.product_name = name;
        this.product_cost = cost;
        this.product_quantity = qty;
        count++;
    }

    public void display() {
        System.out.println("ID: " + product_id + "\tName: " + product_name +
                           "\tCost: ₹" + product_cost + "\tQuantity: " + product_quantity);
    }

    public static void showCount() {
        System.out.println("Total Product Objects Created: " + count);
    }
}

public class Slip_22_Q1 {
    public static void main(String[] args) {
        Product p1 = new Product(101, "Laptop", 65000, 5);
        Product p2 = new Product(102, "Mouse", 800, 20);
        Product p3 = new Product();

        p1.display();
        p2.display();
        p3.display();

        Product.showCount();
    }
}

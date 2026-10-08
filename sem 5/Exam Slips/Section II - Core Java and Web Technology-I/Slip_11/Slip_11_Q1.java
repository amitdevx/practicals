import java.util.Scanner;

class Vehicle {
    String company;
    double price;

    public Vehicle(String company, double price) {
        this.company = company;
        this.price = price;
    }
    
    public void display() {
        System.out.print("Company: " + company + ", Price: ₹" + price);
    }
}

class LightMotorVehicle extends Vehicle {
    double mileage;

    public LightMotorVehicle(String company, double price, double mileage) {
        super(company, price);
        this.mileage = mileage;
    }

    public void display() {
        System.out.print("LMV -> ");
        super.display();
        System.out.println(", Mileage: " + mileage + " km/l");
    }
}

class HeavyMotorVehicle extends Vehicle {
    double capacity_in_tons;

    public HeavyMotorVehicle(String company, double price, double capacity) {
        super(company, price);
        this.capacity_in_tons = capacity;
    }

    public void display() {
        System.out.print("HMV -> ");
        super.display();
        System.out.println(", Capacity: " + capacity_in_tons + " tons");
    }
}

public class Slip_11_Q1 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of vehicles (n): ");
        if (!sc.hasNextInt()) return;
        int n = sc.nextInt();
        
        Vehicle[] vehicles = new Vehicle[n];
        
        for (int i = 0; i < n; i++) {
            System.out.println("Select Vehicle Type for Vehicle " + (i + 1) + ": (1) Light Motor Vehicle (2) Heavy Motor Vehicle");
            int type = sc.nextInt();
            sc.nextLine(); 
            
            System.out.print("Enter Company: ");
            String company = sc.nextLine();
            System.out.print("Enter Price: ");
            double price = sc.nextDouble();
            
            if (type == 1) {
                System.out.print("Enter Mileage: ");
                double mileage = sc.nextDouble();
                vehicles[i] = new LightMotorVehicle(company, price, mileage);
            } else if (type == 2) {
                System.out.print("Enter Capacity in Tons: ");
                double capacity = sc.nextDouble();
                vehicles[i] = new HeavyMotorVehicle(company, price, capacity);
            } else {
                System.out.println("Invalid type. Defaulting to empty vehicle.");
            }
        }
        
        System.out.println("\nVehicle Information\n");
        for (Vehicle v : vehicles) {
            if (v != null) {
                v.display();
            }
        }
        
        sc.close();
    }
}

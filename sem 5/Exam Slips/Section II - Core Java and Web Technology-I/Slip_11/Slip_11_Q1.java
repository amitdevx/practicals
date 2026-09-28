class Vehicle {
    String company;
    double price;

    public Vehicle(String company, double price) {
        this.company = company;
        this.price = price;
    }
}

class LightMotorVehicle extends Vehicle {
    double mileage;

    public LightMotorVehicle(String company, double price, double mileage) {
        super(company, price);
        this.mileage = mileage;
    }

    public void display() {
        System.out.println("LMV -> Company: " + company + ", Price: ₹" + price + ", Mileage: " + mileage + " km/l");
    }
}

class HeavyMotorVehicle extends Vehicle {
    double capacity_in_tons;

    public HeavyMotorVehicle(String company, double price, double capacity) {
        super(company, price);
        this.capacity_in_tons = capacity;
    }

    public void display() {
        System.out.println("HMV -> Company: " + company + ", Price: ₹" + price + ", Capacity: " + capacity_in_tons + " tons");
    }
}

public class Slip_11_Q1 {
    public static void main(String[] args) {
        LightMotorVehicle car = new LightMotorVehicle("Maruti Suzuki", 750000, 22.5);
        HeavyMotorVehicle truck = new HeavyMotorVehicle("Tata Motors", 2800000, 16.0);

        System.out.println("--- Vehicle Information ---");
        car.display();
        truck.display();
    }
}

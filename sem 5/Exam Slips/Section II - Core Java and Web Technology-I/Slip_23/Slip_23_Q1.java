class Continent {
    String continentName;
    public Continent(String cname) {
        this.continentName = cname;
    }
}

class Country extends Continent {
    String countryName;
    public Country(String cname, String country) {
        super(cname);
        this.countryName = country;
    }
}

class State extends Country {
    String stateName;
    String place;

    public State(String cname, String country, String state, String place) {
        super(cname, country);
        this.stateName = state;
        this.place = place;
    }

    public void display() {
        System.out.println("Place:     " + place);
        System.out.println("State:     " + stateName);
        System.out.println("Country:   " + countryName);
        System.out.println("Continent: " + continentName);
    }
}

public class Slip_23_Q1 {
    public static void main(String[] args) {
        State s = new State("Asia", "India", "Maharashtra", "Pune");
        System.out.println("--- Geographical Hierarchy ---");
        s.display();
    }
}

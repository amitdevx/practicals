class Indoor {
    String gameName;
    String[] players;

    public Indoor() {
        this.gameName = "Table Tennis";
        this.players = new String[]{"Player A", "Player B"};
    }

    public Indoor(String gameName, String[] players) {
        this.gameName = gameName;
        this.players = players;
    }

    public void display() {
        System.out.print("Indoor Game: " + gameName + " | Players: ");
        for (String p : players) System.out.print(p + " ");
        System.out.println();
    }
}

class Outdoor {
    String gameName;
    String[] players;

    public Outdoor() {
        this.gameName = "Cricket";
        this.players = new String[]{"Player 1", "Player 2", "Player 3"};
    }

    public Outdoor(String gameName, String[] players) {
        this.gameName = gameName;
        this.players = players;
    }

    public void display() {
        System.out.print("Outdoor Game: " + gameName + " | Players: ");
        for (String p : players) System.out.print(p + " ");
        System.out.println();
    }
}

public class Slip_12_Q1 {
    public static void main(String[] args) {
        Indoor inGame = new Indoor("Chess", new String[]{"Magnus", "Hikaru"});
        Outdoor outGame = new Outdoor("Football", new String[]{"Messi", "Ronaldo", "Neymar"});

        inGame.display();
        outGame.display();
    }
}

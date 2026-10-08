package game;

public class Outdoor {
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

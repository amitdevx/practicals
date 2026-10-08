package game;

public class Indoor {
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

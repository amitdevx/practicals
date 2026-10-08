import game.Indoor;
import game.Outdoor;

public class Slip_12_Q1 {
    public static void main(String[] args) {
        Indoor defaultIn = new Indoor();
        Outdoor defaultOut = new Outdoor();
        
        Indoor inGame = new Indoor("Chess", new String[]{"Magnus", "Hikaru"});
        Outdoor outGame = new Outdoor("Football", new String[]{"Messi", "Ronaldo", "Neymar"});

        defaultIn.display();
        defaultOut.display();
        inGame.display();
        outGame.display();
    }
}

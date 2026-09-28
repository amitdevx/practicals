import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Slip_17_Q1 extends JFrame implements KeyListener {
    public Slip_17_Q1() {
        setTitle("Key Combination Color Switcher");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        addKeyListener(this);
        setFocusable(true);

        JLabel label = new JLabel("Press Ctrl+Alt+O for Orange, Ctrl+Alt+R for Red", JLabel.CENTER);
        add(label);
    }

    public void keyPressed(KeyEvent e) {
        if (e.isControlDown() && e.isAltDown()) {
            if (e.getKeyCode() == KeyEvent.VK_O) {
                getContentPane().setBackground(Color.ORANGE);
            } else if (e.getKeyCode() == KeyEvent.VK_R) {
                getContentPane().setBackground(Color.RED);
            } else if (e.getKeyCode() == KeyEvent.VK_G) {
                getContentPane().setBackground(Color.GREEN);
            }
        }
    }

    public void keyReleased(KeyEvent e) {}
    public void keyTyped(KeyEvent e) {}

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Slip_17_Q1().setVisible(true));
    }
}

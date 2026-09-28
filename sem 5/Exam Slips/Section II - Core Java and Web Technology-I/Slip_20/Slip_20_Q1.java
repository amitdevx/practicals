import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Slip_20_Q1 extends JFrame implements MouseListener, MouseMotionListener {
    JTextField statusField;

    public Slip_20_Q1() {
        setTitle("Mouse Events Handler");
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        statusField = new JTextField("Move or Click mouse inside window");
        statusField.setEditable(false);
        add(statusField, BorderLayout.SOUTH);

        addMouseListener(this);
        addMouseMotionListener(this);
    }

    public void mouseClicked(MouseEvent e) {
        statusField.setText("Mouse Clicked at (" + e.getX() + ", " + e.getY() + ")");
    }

    public void mouseMoved(MouseEvent e) {
        statusField.setText("Mouse Moved at (" + e.getX() + ", " + e.getY() + ")");
    }

    public void mousePressed(MouseEvent e) {}
    public void mouseReleased(MouseEvent e) {}
    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}
    public void mouseDragged(MouseEvent e) {}

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Slip_20_Q1().setVisible(true));
    }
}

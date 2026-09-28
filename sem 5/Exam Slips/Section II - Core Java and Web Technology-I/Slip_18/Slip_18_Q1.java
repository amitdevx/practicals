import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Slip_18_Q1 extends JFrame implements ActionListener {
    JButton redBtn, greenBtn, blueBtn;

    public Slip_18_Q1() {
        setTitle("Color Button App");
        setSize(350, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new FlowLayout());

        redBtn = new JButton("Red");
        greenBtn = new JButton("Green");
        blueBtn = new JButton("Blue");

        redBtn.addActionListener(this);
        greenBtn.addActionListener(this);
        blueBtn.addActionListener(this);

        add(redBtn);
        add(greenBtn);
        add(blueBtn);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == redBtn) {
            getContentPane().setBackground(Color.RED);
            System.out.println("Selected Color: RED");
        } else if (e.getSource() == greenBtn) {
            getContentPane().setBackground(Color.GREEN);
            System.out.println("Selected Color: GREEN");
        } else if (e.getSource() == blueBtn) {
            getContentPane().setBackground(Color.BLUE);
            System.out.println("Selected Color: BLUE");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Slip_18_Q1().setVisible(true));
    }
}

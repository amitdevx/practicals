import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Slip_16_Q1 extends JFrame implements ActionListener {
    DefaultListModel<String> cartModel;
    JList<String> cartList;
    JLabel totalLabel;
    double total = 0.0;

    public Slip_16_Q1() {
        setTitle("Shopping Cart Simulator");
        setSize(400, 350);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout(10, 10));

        JPanel itemPanel = new JPanel(new FlowLayout());
        JButton b1 = new JButton("Notebook (₹50)");
        JButton b2 = new JButton("Pen (₹20)");
        JButton b3 = new JButton("Backpack (₹600)");

        b1.addActionListener(this);
        b2.addActionListener(this);
        b3.addActionListener(this);

        itemPanel.add(b1);
        itemPanel.add(b2);
        itemPanel.add(b3);
        add(itemPanel, BorderLayout.NORTH);

        cartModel = new DefaultListModel<>();
        cartList = new JList<>(cartModel);
        add(new JScrollPane(cartList), BorderLayout.CENTER);

        totalLabel = new JLabel("Total Bill: ₹0.00", JLabel.CENTER);
        totalLabel.setFont(new Font("Arial", Font.BOLD, 16));
        add(totalLabel, BorderLayout.SOUTH);
    }

    public void actionPerformed(ActionEvent e) {
        String item = e.getActionCommand();
        if (item.contains("Notebook")) total += 50;
        else if (item.contains("Pen")) total += 20;
        else if (item.contains("Backpack")) total += 600;

        cartModel.addElement(item);
        totalLabel.setText("Total Bill: ₹" + total);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Slip_16_Q1().setVisible(true));
    }
}

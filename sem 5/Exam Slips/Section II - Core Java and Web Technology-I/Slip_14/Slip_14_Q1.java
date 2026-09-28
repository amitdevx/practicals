import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Slip_14_Q1 extends JFrame implements ActionListener {
    JTextField inputField, outputField;
    JButton processButton;

    public Slip_14_Q1() {
        setTitle("Prime Number Checker");
        setSize(360, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new GridLayout(3, 2, 10, 10));

        add(new JLabel("Enter Number:"));
        inputField = new JTextField();
        add(inputField);

        add(new JLabel("Result:"));
        outputField = new JTextField();
        outputField.setEditable(false);
        add(outputField);

        processButton = new JButton("Process");
        processButton.addActionListener(this);
        add(new JLabel(""));
        add(processButton);
    }

    public boolean isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    public void actionPerformed(ActionEvent e) {
        try {
            int num = Integer.parseInt(inputField.getText().trim());
            if (isPrime(num)) {
                outputField.setText(num + " is a Prime Number");
            } else {
                outputField.setText(num + " is NOT a Prime Number");
            }
        } catch (NumberFormatException ex) {
            outputField.setText("Invalid Integer!");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new Slip_14_Q1().setVisible(true));
    }
}

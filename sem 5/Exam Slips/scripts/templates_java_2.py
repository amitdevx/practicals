# Java Templates for CS-306 Slips 11 to 20

def get_java_slip11_q1():
    return '''class Vehicle {
    String company;
    double price;

    public Vehicle(String company, double price) {
        this.company = company;
        this.price = price;
    }
}

class LightMotorVehicle extends Vehicle {
    double mileage;

    public LightMotorVehicle(String company, double price, double mileage) {
        super(company, price);
        this.mileage = mileage;
    }

    public void display() {
        System.out.println("LMV -> Company: " + company + ", Price: ₹" + price + ", Mileage: " + mileage + " km/l");
    }
}

class HeavyMotorVehicle extends Vehicle {
    double capacity_in_tons;

    public HeavyMotorVehicle(String company, double price, double capacity) {
        super(company, price);
        this.capacity_in_tons = capacity;
    }

    public void display() {
        System.out.println("HMV -> Company: " + company + ", Price: ₹" + price + ", Capacity: " + capacity_in_tons + " tons");
    }
}

public class VehicleHierarchy {
    public static void main(String[] args) {
        LightMotorVehicle car = new LightMotorVehicle("Maruti Suzuki", 750000, 22.5);
        HeavyMotorVehicle truck = new HeavyMotorVehicle("Tata Motors", 2800000, 16.0);

        System.out.println("--- Vehicle Information ---");
        car.display();
        truck.display();
    }
}
'''

def get_java_slip12_q1():
    return '''class Indoor {
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

public class GameDemo {
    public static void main(String[] args) {
        Indoor inGame = new Indoor("Chess", new String[]{"Magnus", "Hikaru"});
        Outdoor outGame = new Outdoor("Football", new String[]{"Messi", "Ronaldo", "Neymar"});

        inGame.display();
        outGame.display();
    }
}
'''

def get_java_slip13_q1():
    return '''public class Clock {
    int hours, minutes, seconds;

    public Clock(int h, int m, int s) {
        if (isValid(h, m, s)) {
            this.hours = h;
            this.minutes = m;
            this.seconds = s;
        } else {
            System.out.println("Invalid time provided! Setting default 00:00:00.");
            this.hours = 0;
            this.minutes = 0;
            this.seconds = 0;
        }
    }

    public boolean isValid(int h, int m, int s) {
        return (h >= 0 && h < 24) && (m >= 0 && m < 60) && (s >= 0 && s < 60);
    }

    public void displayAMPM() {
        String mode = (hours >= 12) ? "PM" : "AM";
        int h12 = (hours % 12 == 0) ? 12 : (hours % 12);
        System.out.printf("Time: %02d:%02d:%02d %s\\n", h12, minutes, seconds, mode);
    }

    public static void main(String[] args) {
        Clock c1 = new Clock(14, 35, 20);
        System.out.print("24-hr Time (14:35:20) in AM/PM mode: ");
        c1.displayAMPM();

        Clock c2 = new Clock(9, 15, 45);
        System.out.print("24-hr Time (09:15:45) in AM/PM mode: ");
        c2.displayAMPM();
    }
}
'''

def get_java_slip14_q1():
    return '''import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class PrimeCheckerGUI extends JFrame implements ActionListener {
    JTextField inputField, outputField;
    JButton processButton;

    public PrimeCheckerGUI() {
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
        SwingUtilities.invokeLater(() -> new PrimeCheckerGUI().setVisible(true));
    }
}
'''

def get_java_slip15_q1():
    return '''import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class SimpleCalculatorGUI extends JFrame implements ActionListener {
    JTextField display;
    double num1 = 0, num2 = 0;
    char operator = ' ';

    public SimpleCalculatorGUI() {
        setTitle("Simple Calculator");
        setSize(300, 400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        display = new JTextField();
        display.setFont(new Font("Arial", Font.BOLD, 20));
        display.setEditable(false);
        add(display, BorderLayout.NORTH);

        JPanel panel = new JPanel(new GridLayout(4, 4, 5, 5));
        String[] buttons = {
            "7", "8", "9", "/",
            "4", "5", "6", "*",
            "1", "2", "3", "-",
            "0", "C", "=", "+"
        };

        for (String text : buttons) {
            JButton btn = new JButton(text);
            btn.setFont(new Font("Arial", Font.BOLD, 16));
            btn.addActionListener(this);
            panel.add(btn);
        }
        add(panel, BorderLayout.CENTER);
    }

    public void actionPerformed(ActionEvent e) {
        String cmd = e.getActionCommand();
        if (cmd.charAt(0) >= '0' && cmd.charAt(0) <= '9') {
            display.setText(display.getText() + cmd);
        } else if (cmd.equals("C")) {
            display.setText("");
            num1 = num2 = 0;
            operator = ' ';
        } else if (cmd.equals("=")) {
            num2 = Double.parseDouble(display.getText());
            double res = 0;
            switch (operator) {
                case '+': res = num1 + num2; break;
                case '-': res = num1 - num2; break;
                case '*': res = num1 * num2; break;
                case '/': res = num2 != 0 ? num1 / num2 : 0; break;
            }
            display.setText(String.valueOf(res));
        } else {
            num1 = Double.parseDouble(display.getText());
            operator = cmd.charAt(0);
            display.setText("");
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new SimpleCalculatorGUI().setVisible(true));
    }
}
'''

def get_java_slip16_q1():
    return '''import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class ShoppingCartGUI extends JFrame implements ActionListener {
    DefaultListModel<String> cartModel;
    JList<String> cartList;
    JLabel totalLabel;
    double total = 0.0;

    public ShoppingCartGUI() {
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
        SwingUtilities.invokeLater(() -> new ShoppingCartGUI().setVisible(true));
    }
}
'''

def get_java_slip17_q1():
    return '''import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class KeyColorChangeGUI extends JFrame implements KeyListener {
    public KeyColorChangeGUI() {
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
        SwingUtilities.invokeLater(() -> new KeyColorChangeGUI().setVisible(true));
    }
}
'''

def get_java_slip18_q1():
    return '''import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class ColorButtonsGUI extends JFrame implements ActionListener {
    JButton redBtn, greenBtn, blueBtn;

    public ColorButtonsGUI() {
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
        SwingUtilities.invokeLater(() -> new ColorButtonsGUI().setVisible(true));
    }
}
'''

def get_java_slip19_q1():
    return '''import java.io.*;
import java.util.Scanner;

public class FileCounter {
    public static void main(String[] args) {
        String filename = "sample.txt";
        // Create demo file
        try (FileWriter fw = new FileWriter(filename)) {
            fw.write("Java practical examination.\\nSem V computer science.\\nWeb technology practicals.");
        } catch (IOException e) {
            System.out.println("Error initializing file.");
        }

        int charCount = 0, wordCount = 0, lineCount = 0;

        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
            String line;
            while ((line = br.readLine()) != null) {
                lineCount++;
                charCount += line.length();
                String[] words = line.trim().split("\\\\s+");
                if (words.length > 0 && !words[0].isEmpty()) {
                    wordCount += words.length;
                }
            }
            System.out.println("File: " + filename);
            System.out.println("Total Characters: " + charCount);
            System.out.println("Total Words:      " + wordCount);
            System.out.println("Total Lines:      " + lineCount);
        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }
}
'''

def get_java_slip20_q1():
    return '''import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MouseEventsGUI extends JFrame implements MouseListener, MouseMotionListener {
    JTextField statusField;

    public MouseEventsGUI() {
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
        SwingUtilities.invokeLater(() -> new MouseEventsGUI().setVisible(true));
    }
}
'''

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class Slip_15_Q1 extends Application {
    
    private TextField display;
    private double num1 = 0, num2 = 0;
    private char operator = ' ';
    private boolean startNew = true;

    @Override
    public void start(Stage primaryStage) {
        display = new TextField();
        display.setEditable(false);
        display.setStyle("-fx-font-size: 20px;");

        GridPane grid = new GridPane();
        grid.setHgap(5);
        grid.setVgap(5);

        String[] buttons = {
            "7", "8", "9", "/",
            "4", "5", "6", "*",
            "1", "2", "3", "-",
            "0", "C", "=", "+"
        };

        int row = 0, col = 0;
        for (String text : buttons) {
            Button btn = new Button(text);
            btn.setMinSize(50, 50);
            btn.setStyle("-fx-font-size: 16px;");
            btn.setOnAction(e -> handleButton(text));
            grid.add(btn, col, row);
            col++;
            if (col == 4) {
                col = 0;
                row++;
            }
        }

        VBox layout = new VBox(10, display, grid);
        layout.setPadding(new Insets(10));
        
        Scene scene = new Scene(layout, 250, 320);
        primaryStage.setTitle("Simple Calculator");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void handleButton(String text) {
        if (text.matches("[0-9]")) {
            if (startNew) {
                display.setText(text);
                startNew = false;
            } else {
                display.setText(display.getText() + text);
            }
        } else if (text.equals("C")) {
            display.setText("");
            num1 = num2 = 0;
            operator = ' ';
            startNew = true;
        } else if (text.equals("=")) {
            if (!startNew && operator != ' ') {
                num2 = Double.parseDouble(display.getText());
                double res = 0;
                switch (operator) {
                    case '+': res = num1 + num2; break;
                    case '-': res = num1 - num2; break;
                    case '*': res = num1 * num2; break;
                    case '/': res = num2 != 0 ? num1 / num2 : 0; break;
                }
                display.setText(String.valueOf(res));
                startNew = true;
                operator = ' ';
            }
        } else { // Operator
            if (!display.getText().isEmpty()) {
                num1 = Double.parseDouble(display.getText());
                operator = text.charAt(0);
                startNew = true;
            }
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}

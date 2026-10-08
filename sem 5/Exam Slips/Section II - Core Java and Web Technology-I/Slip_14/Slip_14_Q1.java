import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class Slip_14_Q1 extends Application {
    
    public boolean isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    @Override
    public void start(Stage primaryStage) {
        TextField inputField = new TextField();
        inputField.setPromptText("Enter a number");

        Button processButton = new Button("Process");
        Label resultLabel = new Label("Result:");

        processButton.setOnAction(e -> {
            try {
                int num = Integer.parseInt(inputField.getText().trim());
                if (isPrime(num)) {
                    resultLabel.setText(num + " is a Prime Number");
                } else {
                    resultLabel.setText(num + " is NOT a Prime Number");
                }
            } catch (NumberFormatException ex) {
                resultLabel.setText("Invalid Integer!");
            }
        });

        VBox layout = new VBox(10);
        layout.setAlignment(Pos.CENTER);
        layout.getChildren().addAll(new Label("Enter Number:"), inputField, processButton, resultLabel);

        Scene scene = new Scene(layout, 300, 200);
        primaryStage.setTitle("Prime Number Checker");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}

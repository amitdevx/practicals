import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

public class Slip_17_Q1 extends Application {
    @Override
    public void start(Stage primaryStage) {
        StackPane root = new StackPane();
        Label label = new Label("Press Ctrl+Alt+O for Orange, Ctrl+Alt+R for Red");
        root.getChildren().add(label);

        Scene scene = new Scene(root, 400, 300);

        scene.addEventHandler(KeyEvent.KEY_PRESSED, e -> {
            if (e.isControlDown() && e.isAltDown()) {
                if (e.getCode() == KeyCode.O) {
                    root.setStyle("-fx-background-color: orange;");
                } else if (e.getCode() == KeyCode.R) {
                    root.setStyle("-fx-background-color: red;");
                }
            }
        });

        primaryStage.setTitle("Key Combination Color Switcher");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}

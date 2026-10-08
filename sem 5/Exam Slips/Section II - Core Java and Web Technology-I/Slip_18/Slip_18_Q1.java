import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.layout.HBox;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

public class Slip_18_Q1 extends Application {
    @Override
    public void start(Stage primaryStage) {
        StackPane root = new StackPane();
        HBox buttons = new HBox(10);
        buttons.setAlignment(Pos.CENTER);

        Button redBtn = new Button("Red");
        Button greenBtn = new Button("Green");
        Button blueBtn = new Button("Blue");

        redBtn.setOnAction(e -> { root.setStyle("-fx-background-color: red;"); System.out.println("RED"); });
        greenBtn.setOnAction(e -> { root.setStyle("-fx-background-color: green;"); System.out.println("GREEN"); });
        blueBtn.setOnAction(e -> { root.setStyle("-fx-background-color: blue;"); System.out.println("BLUE"); });

        buttons.getChildren().addAll(redBtn, greenBtn, blueBtn);
        root.getChildren().add(buttons);

        primaryStage.setScene(new Scene(root, 350, 200));
        primaryStage.setTitle("Color Button App");
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}

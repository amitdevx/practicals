import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.layout.VBox;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;

public class Slip_16_Q1 extends Application {
    private double total = 0.0;

    @Override
    public void start(Stage primaryStage) {
        ListView<String> cartList = new ListView<>();
        Label totalLabel = new Label("Total Bill: ₹0.00");

        Button b1 = new Button("Notebook (₹50)");
        Button b2 = new Button("Pen (₹20)");
        Button b3 = new Button("Backpack (₹600)");

        b1.setOnAction(e -> { cartList.getItems().add("Notebook (₹50)"); total += 50; update(totalLabel); });
        b2.setOnAction(e -> { cartList.getItems().add("Pen (₹20)"); total += 20; update(totalLabel); });
        b3.setOnAction(e -> { cartList.getItems().add("Backpack (₹600)"); total += 600; update(totalLabel); });

        HBox buttons = new HBox(10, b1, b2, b3);
        VBox root = new VBox(10, buttons, cartList, totalLabel);
        root.setPadding(new Insets(10));

        primaryStage.setScene(new Scene(root, 400, 300));
        primaryStage.setTitle("Shopping Cart");
        primaryStage.show();
    }

    private void update(Label totalLabel) {
        totalLabel.setText("Total Bill: ₹" + total);
    }

    public static void main(String[] args) {
        launch(args);
    }
}

package projet_reseau;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

public class HelloFX extends Application {

    @Override
    public void start(Stage stage) {
        String javaVersion = System.getProperty("java.version");
        String javafxVersion = System.getProperty("javafx.version");
        Label l = new Label("Hello, JavaFX " + javafxVersion + ", running on Java " + javaVersion + ".");
        Label l1 = new Label("Mange tes morts");
        Scene scene = new Scene(new StackPane(l), 640, 480);
        Scene scene2 = new Scene(new StackPane(l1), 630, 480);
        stage.setScene(scene2);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }

}

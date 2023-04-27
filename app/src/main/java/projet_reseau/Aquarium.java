package projet_reseau;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.layout.Pane;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import java.io.File;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.control.Label;
import javafx.scene.text.FontWeight;
import javafx.scene.control.Menu;
import javafx.scene.control.MenuBar;
import javafx.scene.control.MenuItem;
import javafx.scene.layout.VBox;
import java.util.HashMap;
import java.util.HashSet;

public class Aquarium extends Application {

    private static final int WIDTH = 800;
    private static final int HEIGHT = 600;
    private static final int FISH_RADIUS = 25;
    private static final int FISH_SPEED = 5;
    private Console console;
    VBox root;

    @Override
    public void init() throws Exception {
        client = new Client();
    }

    @Override
    public void start(Stage primaryStage) throws Exception {
        console = new Console(this,400, 400);
        console.show();
        myFish = new Fish("/home/brice/Projet_Reseau/projet_reseau/app/src/main/images/blobfish.png");
        Group fish1 = myFish.addGroupFish();
        fish1.setLayoutX(random.nextInt(WIDTH));
        fish1.setLayoutY(random.nextInt(HEIGHT));

        Scene scene = new Scene(fish1, WIDTH, HEIGHT, Color.BLUE);

        primaryStage.setScene(scene);
        primaryStage.show();

        AnimationTimer timer = new AnimationTimer() {
            @Override
            public void handle(long now) {
                gc.drawImage(backgroundImage, 0, 0);
                for (Fish f : client.getFishs()) {
                    gc.drawImage(f.getImage(),
                        f.getX() * canvas.getWidth() / 100, 
                        f.getY() * canvas.getHeight() / 100,
                        f.getWidth() * canvas.getWidth() / 100,
                        f.getHeight() * canvas.getHeight() / 100);
                    f.moveFish(WIDTH,HEIGHT);
                }
            }
        };

        timer.start();

        consoleItem.setOnAction(new EventHandler<ActionEvent>(){
            @Override
            public void handle(ActionEvent event) {
                console = new Console(client);
                console.show();
            }
        });

        logOutItem.setOnAction(new EventHandler<ActionEvent>(){
            @Override
            public void handle(ActionEvent event){
               client.handleCommand("log out");
            }
        });

        exitItem.setOnAction(new EventHandler<ActionEvent>(){
            @Override
            public void handle(ActionEvent event){
                client.handleCommand("log out");
                System.exit(0);
            }
        });

    }
    public static void main(String[] args) {
        launch();
    }
}

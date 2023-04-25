package projet_reseau;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Polygon;
import javafx.stage.Stage;

import java.util.Random;
import java.util.Collection; 
import java.io.*;

public class Aquarium extends Application {

    private static final int WIDTH = 800;
    private static final int HEIGHT = 600;
    private static final int FISH_RADIUS = 25;
    private static final int FISH_SPEED = 5;
    private Console console;
    private Fish myFish;

    private int dx = FISH_SPEED;
    private int dy = FISH_SPEED;

    private Random random = new Random();

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
                // Move the fish
                fish1.setLayoutX(fish1.getLayoutX() + dx);
                fish1.setLayoutY(fish1.getLayoutY() + dy);

                // Check for collision with the edges of the screen
                if (fish1.getLayoutX() <= 0 || fish1.getLayoutX() + FISH_RADIUS * 2 >= WIDTH) {
                    dx = -dx;
                }
                if (fish1.getLayoutY() <= 0 || fish1.getLayoutY() + FISH_RADIUS * 2 >= HEIGHT) {
                    dy = -dy;
                }
            }
        };

        timer.start();
    }

    public static void main(String[] args) {
        launch();
    }
}

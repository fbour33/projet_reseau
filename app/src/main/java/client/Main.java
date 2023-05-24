package client;

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
import javafx.animation.KeyFrame;
import javafx.animation.KeyValue;
import javafx.animation.Timeline;
import javafx.util.Duration;
import javafx.scene.Node;

public class Main extends Application {

    public static final int WIDTH = 1000;
    public static final int HEIGHT = 900;
    private static Client client;
    private Timeline timeline;
    private Console console;
    VBox root;
    public static Pane affichage;

    @Override
    public void init() throws Exception {
        client = new Client();
    }

    @Override
    public void start(Stage primaryStage) throws Exception {

        /**
        * Création d'une vbox qui va contenir notre menu et notre vue
        */   
        root = new VBox();

        /**
        * création du menu et ajout d'items 
        */
        
        MenuBar menuBar = new MenuBar();
        Menu AquariumMenu = new Menu();
        Label aquariumLabel = new Label("Aquarium Menu");
        aquariumLabel.setTextFill(Color.BLACK); 
        aquariumLabel.setFont(Font.font("Monospace", FontWeight.BOLD, 25));
        AquariumMenu.setGraphic(aquariumLabel);

        MenuItem consoleItem = new MenuItem();
        Label consoleItemLabel = new Label("Open console");
        consoleItemLabel.setTextFill(Color.BLACK); 
        consoleItemLabel.setFont(Font.font("Monospace", FontWeight.BOLD, 15));
        consoleItem.setGraphic(consoleItemLabel);

        MenuItem logOutItem = new MenuItem();
        Label logOutItemLabel = new Label("Log out");
        logOutItemLabel.setTextFill(Color.BLACK); 
        logOutItemLabel.setFont(Font.font("Monospace", FontWeight.BOLD, 15));
        logOutItem.setGraphic(logOutItemLabel);

        MenuItem exitItem = new MenuItem();
        Label exitItemLabel = new Label("Log out and Exit");
        exitItemLabel.setTextFill(Color.BLACK); 
        exitItemLabel.setFont(Font.font("Monospace", FontWeight.BOLD, 15));
        exitItem.setGraphic(exitItemLabel);

        /**
         * Ajout des items au menu et du menu à la barre de menu
         */
         
        AquariumMenu.getItems().addAll(consoleItem,logOutItem,exitItem);
        menuBar.getMenus().addAll(AquariumMenu);

        /**
         * création d'un canva et d'un GraphicsContext
         */
        Canvas canvas = new Canvas(WIDTH,HEIGHT);
        GraphicsContext gc = canvas.getGraphicsContext2D();
        
        /**
         * création d'un panel qui va contenir notre canvas
         */ 
        affichage = new Pane();
        affichage.getChildren().addAll(canvas);
        

        /**
         * ajout de la barre de menu et du panel d'affichage à la Vbox
         */
        root.getChildren().addAll(menuBar,affichage);

        /**
         * création de l'image de background
         */
        File bgfile = new File("bg.png");
        String bgAbsolutePath = bgfile.getAbsolutePath();
        bgAbsolutePath = bgAbsolutePath.replace("bg.png", "src/main/images/bg.png");
        Image backgroundImage = new Image("file:"+bgAbsolutePath);

        gc.clearRect(0, 0, canvas.getWidth(), canvas.getHeight());
        gc.drawImage(backgroundImage, 0, 0);
        /**
         * création de la scène et ajout de notre Vbox à la scène
         */

        Scene scene = new Scene(root, WIDTH, HEIGHT);
        primaryStage.setScene(scene);
        primaryStage.show();

        timeline = new Timeline();
        timeline.setCycleCount(Timeline.INDEFINITE);
        timeline.getKeyFrames().add(
            new KeyFrame(Duration.millis(500.),
            new EventHandler<ActionEvent>() {
                @Override
                public void handle(ActionEvent arg0) {
                    client.updateFishes();
                }
            },new KeyValue[0])
        );
        timeline.playFromStart();

        /**
         * ajout des évènements liés aux items 
         */
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
               client.logOut();
            }
        });

        exitItem.setOnAction(new EventHandler<ActionEvent>(){
            @Override
            public void handle(ActionEvent event){
                client.logOut();
                System.exit(0);
            }
        });

    }

    public static void delFish(Fish fish){
        affichage.getChildren().remove(fish.getImageView());
    }

    public static void addFish(Fish fish){
        affichage.getChildren().add(fish.getImageView());
    }

    public static void main(String[] args) {
        launch();    
    }

}
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
    private static final int WIDTH = 1000;
    private static final int HEIGHT = 800;
    private static Client client;

    private Console console;
    VBox root;

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
        Pane affichage = new Pane();
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

        /**
         * création de la scène et ajout de notre Vbox à la scène
         */

        Scene scene = new Scene(root, WIDTH, HEIGHT);
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
                    if(f.isRunning()){
                        f.moveFish(WIDTH,HEIGHT,gc);   
                    }
                }
            }
        };
        timer.start();

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

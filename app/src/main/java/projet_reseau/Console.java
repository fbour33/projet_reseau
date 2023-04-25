package projet_reseau;

import javafx.scene.Scene;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.Label;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.control.*;
import javafx.scene.input.KeyCode;

public class Console extends Stage{
    
    StackPane stackpane;
    HBox hbox;
    private TextField input;
    protected TextArea output;
    private int width;
    private int height;
    public Aquarium aquarium;
    protected Parser parser;
    public Console(Aquarium aquarium,int w, int h){
        width = w;
        height = h;
        initDisplay();
        parser = new Parser(this, output);
    }

    private void initDisplay(){
        this.setTitle("Console de l'affichage");
        stackpane = new StackPane();

        Label promptLabel = new Label("$");
        promptLabel.setTextFill(Color.GREEN); 
        promptLabel.setFont(Font.font("Monospace", FontWeight.BOLD, 25));

        input = new TextField();
        input.setStyle("-fx-background-color: black; -fx-text-fill: green; -fx-font-family: monospace; -fx-font-size: 14pt; -fx-padding: 5px;");
        input.setPrefWidth(400);
        input.setOnKeyPressed(event -> {
            if (event.getCode() == KeyCode.ENTER) { 
                String command = input.getText();
                executeCommand(command);
                input.clear();
            }
        });

        output = new TextArea();
        output.setEditable(false);
        output.setStyle("-fx-background-color: black; -fx-text-fill: green; -fx-font-family: monospace; -fx-font-size: 14pt; -fx-border-width: 0px; -fx-padding: 5px; -fx-control-inner-background: black;");
        output.setPrefWidth(400);
        output.setPrefHeight(200);
        output.setWrapText(true);

        hbox = new HBox();
        hbox.setStyle("-fx-background-color: black;");
        hbox.getChildren().addAll(promptLabel,input);
        stackpane.getChildren().add(hbox);

        VBox vbox = new VBox();
        vbox.setStyle("-fx-background-color: black; -fx-text-fill: white; -fx-font-family: monospace; -fx-font-size: 14pt;");
        vbox.getChildren().addAll(hbox, output);
        stackpane.getChildren().add(vbox);

        Scene scene = new Scene(stackpane, width, height);
        scene.setFill(Color.BLACK);
        this.setScene(scene);
    }

    private void executeCommand(String command) {
        // Écrire ici votre code pour exécuter la commande saisie
        parser.parserAction(command);
    }
}

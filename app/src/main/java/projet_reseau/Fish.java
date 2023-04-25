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

public class Fish {

    private ImageView myFish; 
    static final private int WIDTH = 150; 
    static final private int HEIGHT = 150; 

    Fish(String image) throws FileNotFoundException {
        myFish = new ImageView(new Image(new FileInputStream(image))); 
        myFish.setFitWidth(WIDTH); 
        myFish.setFitHeight(HEIGHT); 
        //myFish = new Group(myFish)
    }

    Group addGroupFish(){
        return new Group(myFish);
    }
}
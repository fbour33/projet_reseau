package projet_reseau;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.scene.*;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.canvas.GraphicsContext;
import javafx.stage.Stage;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Random;
import java.util.Collection; 
import java.io.*;

public class Fish {

    private ImageView myFish; 
    private Image myFishImage; 
    private int WIDTH; 
    private int HEIGHT; 
    private String name;
    private double x;
    private double y;
    private double xGoal;
    private double yGoal;
    private boolean running;
    private int timeToGetGoal;
    private String strategy;

    public Fish(String fishName, double posX, double posY, int width, int height, int time) {
        initFishImageView(fishName);
        setPosition(posX, posY);
        name = fishName;
        running = false;
        xGoal = -1;
        yGoal = -1;
        WIDTH = width;
        HEIGHT = height;
        timeToGetGoal = time;
    }

    private void initFishImageView(String fishName){
        String imageName = fishName;
        int underscoreIndex = imageName.indexOf("_");
        imageName = imageName.substring(0, underscoreIndex);
        if (!imageName.endsWith(".png")) {
            imageName += ".png";
        }
        File file = new File(imageName);
        String absolutePath = file.getAbsolutePath();
        absolutePath = absolutePath.replace(imageName, "src/main/images/"+imageName);
        final Image img = new Image("file:"+absolutePath);
        myFishImage = img;
        myFish = new ImageView(img);
        myFish.setFitHeight(HEIGHT);
        myFish.setFitWidth(WIDTH);
    }

    public ImageView getImageView(){
        return myFish;
    }

    public Image getImage(){
        return myFishImage;
    }

    public double getX(){
        return x;
    }
    public double getY(){
        return y;
    }

    public double getWidth(){
        return WIDTH;
    }
    public double getHeight(){
        return HEIGHT;
    }

    public String getName(){
        return name;
    }
    public void setPosition(double newX, double newY) {
        x = newX;
        y = newY;

        myFish.setX(x);
        myFish.setY(y);
    }

    public void setGoal(double goalX, double goalY){
        xGoal = goalX;
        yGoal = goalY;
    }

    public boolean isRunning() {
        return running;
    }

    public void moveFish(int width, int height, GraphicsContext gc){
        if(timeToGetGoal!=0){
            x = x + (xGoal - x)/timeToGetGoal;
            y = y + (yGoal - y)/timeToGetGoal;
        }else{
            x = xGoal;
            y = yGoal;
        }
    }
}
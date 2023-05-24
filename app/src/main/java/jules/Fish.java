package client;

import javafx.scene.image.Image;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.io.*;
import java.lang.*; 
import java.util.*; 
import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.Queue;
import javafx.animation.TranslateTransition;
import javafx.scene.image.ImageView;
import javafx.util.Duration;

public class Fish { 
    private Image myFishImage;
    private ImageView imageView;
    private int WIDTH; 
    private int HEIGHT; 
    private String name;
    private int x;
    private int y;
    private boolean running;
    private double elapsedTime;
    private int time;
    public ArrayList<Goal> goals;
    public TranslateTransition transi;
    
    /**
     * Conctructeur du poisson 
     */
    public Fish(String fishName, int posX, int posY, int width, int height) {
        setPosition(posX, posY);
        WIDTH = width*Main.WIDTH/100;
        HEIGHT = height*Main.HEIGHT/100;
        initFishImage(fishName);
        goals = new ArrayList<Goal>(); 
        name = fishName;
        running = false;
        time = 100;
    }

    /*************************************************************************/
    /*                             GETTER                                   */
    /***********************************************************************/

    /**
     * Récupère l'image du poisson
     * @return myFishImage qui est une variable globale contenant l'image du poisson 
     */
    public Image getImage(){
        return myFishImage;
    }

    public ImageView getImageView(){
        return imageView;
    }    

    /**
     * Récupère l'abscisse du poisson 
     * @return x qui est une variable globale contenant l'abscisse du poisson  
     */
    public int getX(){
        return x;
    }

    /**
     * Récupère l'ordonnée du poisson 
     * @return y qui est une variable globale contenant l'ordonnée du poisson  
     */
    public int getY(){
        return y;
    }

    /**
     * Récupère la largeur du poisson en pourcentage de celle de l'aquarium  
     * @return WIDTH qui est une variable globale contenant la largeur du poisson  
     */
    public int getWidth(){
        return WIDTH;
    }

    /**
     * Récupère la hauteur du poisson en pourcentage de celle de l'aquarium  
     * @return HEIGHT qui est une variable globale contenant la hauteur du poisson  
     */
    public int getHeight(){
        return HEIGHT;
    }

    /**
     * Récupère le nom du poisson  
     * @return name qui est une variable globale contenant le nom du poisson  
     */
    public String getName(){
        return name;
    }

    public Goal getCurrentGoal(){
        if(!goals.isEmpty()){
            return goals.get(0);
        }
        else return null;
    }


    /*************************************************************************/
    /*                             SETTER                                   */
    /***********************************************************************/

    /**
     * Définir la position du poisson 
     */

    public void setPosition(int newX, int newY) {
        x = newX*Main.WIDTH/100;
        y = newY*Main.HEIGHT/100;
    }

    /**
     * Définir les nouveaux objectifs du poisson 
     */
    public void addGoal(Goal goal){
        goals.add(goal);
    }

    /**
     * Démarrer ou freeze le poisson
     */
    public void setRunning(boolean bool){
        running = bool;
    }

    /**
     * Donner le temps pour atteindre l'objectif
     */
    public void setTime(int time){
        this.time = time; 
    }

    /*************************************************************************/
    /*                     SIDE FUNCTIONS                                   */
    /***********************************************************************/

    /**
     *  Parse le nom du poisson
     *  L'objectif est de rétirer l'underscored du nom du poisson
     */
    private String parseName(String fishName) {
        String nameParsed = fishName;
        int underscoreIndex = nameParsed.indexOf("_");
        if(underscoreIndex != -1){
            nameParsed = nameParsed.substring(0, underscoreIndex);
        }
        return nameParsed;
    }

    /**
     * Initialise l'image du poisson 
     */
    private void initFishImage(String fishName){
        String imageName = parseName(fishName);
        if (!imageName.endsWith(".png")) {
            imageName += ".png";
        }
        File file = new File(imageName);
        String absolutePath = file.getAbsolutePath();
        absolutePath = absolutePath.replace(imageName, "src/main/images/"+imageName);
        final Image img = new Image("file:"+absolutePath);
        myFishImage = img;
        imageView = new ImageView();
        imageView.setImage(myFishImage);
        imageView.setX(x);
        imageView.setY(y);
        imageView.setFitWidth(WIDTH);
        imageView.setFitHeight(HEIGHT);

    }

    /**
     * retourne l'état du poisson 
     */
    public boolean isRunning() {
        return running;
    }

    public void start(){
        running = true;
        transi = new TranslateTransition();
        transi.setNode(imageView);
        transi.setCycleCount(1);
    }

    public boolean goalsContains(int x, int y){
        for(Goal g : goals){
            if (g.x == x && g.y == y){
                return true;
            }
        }
        return false;
    }

    public void update(){
        if(goals.isEmpty()){
            return;
        }
        Goal currentGoal = goals.get(0);
        currentGoal.timeLeft -= 1;
        goals.set(0, currentGoal);
        if(currentGoal.timeLeft <= 0){
            transi.stop();
            x = currentGoal.x;
            y = currentGoal.y;
            goals.remove(0);
            currentGoal = goals.get(0);

            transi.setDuration(Duration.millis(currentGoal.timeLeft*1000));
            transi.setByX((currentGoal.x -x)*Main.WIDTH/100);
            transi.setByY((currentGoal.y -y)*Main.HEIGHT/100);

            transi.play();
        }
    }

    
}
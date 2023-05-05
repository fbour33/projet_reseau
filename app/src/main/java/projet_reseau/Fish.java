package projet_reseau;


import javafx.scene.image.Image;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.io.*;
import java.lang.*; 
import java.util.*; 
import java.awt.geom.Point2D;

public class Fish { 
    private Image myFishImage; 
    private double WIDTH; 
    private double HEIGHT; 
    private String name;
    private double x;
    private double y;
    private double xGoal;
    private double yGoal;
    private boolean running;
    private int timeToGetGoal;
    private ArrayList<Point2D> xyGoal;
    
    /**
     * Conctructeur du poisson 
     */
    public Fish(String fishName, double posX, double posY, double width, double height) {
        initFishImage(fishName);
        setPosition(posX, posY);
        xyGoal = new ArrayList<Point2D>(); 
        name = fishName;
        running = true;
        WIDTH = width;
        HEIGHT = height;
        timeToGetGoal = 100;
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

    /**
     * Récupère l'abscisse du poisson 
     * @return x qui est une variable globale contenant l'abscisse du poisson  
     */
    public double getX(){
        return x;
    }

    /**
     * Récupère l'ordonnée du poisson 
     * @return y qui est une variable globale contenant l'ordonnée du poisson  
     */
    public double getY(){
        return y;
    }

    /**
     * Récupère la largeur du poisson en pourcentage de celle de l'aquarium  
     * @return WIDTH qui est une variable globale contenant la largeur du poisson  
     */
    public double getWidth(){
        return WIDTH;
    }

    /**
     * Récupère la hauteur du poisson en pourcentage de celle de l'aquarium  
     * @return HEIGHT qui est une variable globale contenant la hauteur du poisson  
     */
    public double getHeight(){
        return HEIGHT;
    }

    /**
     * Récupère le nom du poisson  
     * @return name qui est une variable globale contenant le nom du poisson  
     */
    public String getName(){
        return name;
    }


    /*************************************************************************/
    /*                             SETTER                                   */
    /***********************************************************************/

    /**
     * Définir la position du poisson 
     */

    public void setPosition(double newX, double newY) {
        x = newX;
        y = newY;
    }

    /**
     * Définir les nouveaux objectifs du poisson 
     */
    public void setGoalList(Point2D position){
        xyGoal.add(position);
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
        timeToGetGoal = time; 
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
    }

    /**
     * retourne l'état du poisson 
     */
    public boolean isRunning() {
        return running;
    }

    /**
     * met à jour la position du poisson 
     */
    public void moveFish(int width, int height){
        //System.out.println("Je m'exécute");
        if(!xyGoal.isEmpty()){
            //System.out.println("Je m'exécute");
            if(timeToGetGoal!=0){
                Point2D point = xyGoal.get(0);
                x = x + (point.getX() - x)/timeToGetGoal;
                y = y + (point.getY() - y)/timeToGetGoal;
                xyGoal.remove(0);
            }else{
                x = (xyGoal.get(0)).getX();
                y = (xyGoal.get(0)).getY();
            }
        }
    }
    
}
package projet_reseau;

import java.lang.*; 
import java.util.*; 
import java.io.*;
import java.awt.geom.Point2D;

public class getProperties {
    private String[] command;
    private String[] response;  
    private Point2D position; 
    private Point2D size; 

    private getProperties(){
        position = new Point2D.Double(0, 0); 
        size = new Point2D.Double(0, 0);
    }

    public void getStringServer(String senderCommand, String receiverResponse){
        command = senderCommand.split(" "); 
        if(command[0].equals("addFish")){
            ArrayList<String> list = new ArrayList<String>(Arrays.asList(command));
            list.remove("at"); 
            String[] position = list.get(2).split(",");
            list.remove(list.get(2)); 
            for(int i = 0; i < 2; i++)
                list.add(i+2, position[i]);
            command = list.toArray(new String[list.size()]);
        }
        if(receiverResponse != "OK")
            response = receiverResponse.split(" : ");
        else
            response = receiverResponse.split(" ");  
    }

    public void changeProperties(){
        //Change position properties
        String[] separatedPosition = command[2].split("x");
        position.setLocation(Double.parseDouble(separatedPosition[0]), Double.parseDouble(separatedPosition[1])); 

        //Change size properties
        String[] separatedSize = command[3].split("x"); 
        size.setLocation(Double.parseDouble(separatedSize[0]), Double.parseDouble(separatedSize[1]));
    }

    public String[] getCommand(){
        return Arrays.copyOf(command, command.length); 
    }

    public String[] getResponse(){
        return Arrays.copyOf(response, response.length); 
    }

    public Point2D getPosition(){
        return new Point2D.Double(position.getX(), position.getY()); 
    }

    static public void main(String[] args){
        String senderCommand = "addFish Nemo at 42x50,4x3, RandomWayPoint"; 
        String receiverReponse = " NOK : modèle de mobilité non supporté"; 
        getProperties props = new getProperties();
        props.getStringServer(senderCommand, receiverReponse); 
        System.out.println(Arrays.toString(props.getCommand()));  
        System.out.println(Arrays.toString(props.getResponse())); 
        props.changeProperties();
        System.out.println(props.getPosition().getX()); 
    }
}
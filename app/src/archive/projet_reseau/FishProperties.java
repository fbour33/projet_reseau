package projet_reseau;

import java.lang.*; 
import java.util.*; 
import java.io.*;
import java.awt.geom.Point2D;

public class FishProperties {
    private String[] command;
    private String[] response; 

    public FishProperties(){}

    public String[] parser(String str){
        str = str.replaceAll("\\,", " ");
        str = str.replaceAll("\\[|\\]|at|\\:", ""); 
        String[] elements = str.split("\\s+");
        return elements;
    }

    public void getStringServer(String senderCommand, String receiverResponse){
        command = parser(senderCommand);

        if(command[0].equals("ls")){
            receiverResponse = receiverResponse.replaceFirst("list ", "");
            response = receiverResponse.split("(?<=\\])\\s");
        }else{
            response = receiverResponse.split(" ");
        }
    }

    public Point2D createPosition(String[] fishes){
        System.out.println(" fishes length " + fishes.length);
        if(fishes.length > 1) {
            int index = 2; 
            if(!fishes[0].equals("addFish"))
                index = 1; 
            String[] separatedPosition = fishes[index].split("x");
            return new Point2D.Double(Double.parseDouble(separatedPosition[0]), Double.parseDouble(separatedPosition[1]));
        }
        return new Point2D.Double(-1, -1);
    }

    public Point2D createSize(String[] fishes){
        int index = 3; 
        if(!fishes[0].equals("addFish"))
            index = 2; 
        String[] separatedSize = fishes[index].split("x");
        return new Point2D.Double(Double.parseDouble(separatedSize[0]), Double.parseDouble(separatedSize[1]));
    }

    public ArrayList<String[]> parsedFishList(String[] response){
        ArrayList<String[]> fishesProperties = new ArrayList<String[]>();
        if(command[0].equals("ls")){ 
            for(int i = 0; i < response.length; ++i){
                fishesProperties.add(parser(response[i]));
            }
        }
        return fishesProperties; 
    }

    public String[] getCommand(){
        return Arrays.copyOf(command, command.length); 
    }

    public String[] getResponse(){
        return Arrays.copyOf(response, response.length); 
    }
}

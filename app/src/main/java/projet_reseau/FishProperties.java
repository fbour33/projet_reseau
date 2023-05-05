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
        str = str.replaceAll("\\[|\\]|at|\\:", ""); 
        str = str.replaceAll("\\, ", ","); 
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
        String[] separatedPosition = fishes[2].split("x");
        return new Point2D.Double(Double.parseDouble(separatedPosition[0]), Double.parseDouble(separatedPosition[1]));
    }

    public Point2D createSize(String[] fishes){
        String[] separatedSize = fishes[3].split("x");
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

    //public static void main(String[] args){
    //    FishProperties fish = new FishProperties(); 
    //    fish.getStringServer("ls", "list [PoissonRouge at 92x40,10x4,5] [PoissonClown at 22x80,12x6,5]");
    //    ArrayList<String[]> test = fish.changeLsProperties(fish.getResponse());
    //    for(String[] e : test){
    //        System.out.println(Arrays.toString(e)); 
    //    }
    //    //System.out.println(Arrays.toString(fish.parser("NOK : Ok")));
    //    fish.getStringServer("addFish ClownFish at 61x52,4x3, RandomWayPoint", "OK");
    //    System.out.println(Arrays.toString(fish.getCommand())); 
    //    System.out.println(Arrays.toString(fish.getResponse())); 
    //    fish.getStringServer("delFish ClownFish", "OK");
    //    System.out.println(Arrays.toString(fish.getCommand())); 
    //    System.out.println(Arrays.toString(fish.getResponse())); 
    //    fish.getStringServer("startFish ClownFish", "NOK : baguette");
    //    System.out.println(Arrays.toString(fish.getCommand())); 
    //    System.out.println(Arrays.toString(fish.getResponse())); 
    //}

}


    //public void createPositionSize(String[] fishes){
    //        //Change position properties
    //        String[] separatedPosition = fishes[2].split("x");
    //        position.setLocation(Double.parseDouble(separatedPosition[0]), Double.parseDouble(separatedPosition[1])); 
//
    //        //Change size properties
    //        String[] separatedSize = fishes[3].split("x"); 
    //        size.setLocation(Double.parseDouble(separatedSize[0]), Double.parseDouble(separatedSize[1]));
    //}
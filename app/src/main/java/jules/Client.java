package jules;

import java.io.*;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javafx.scene.layout.Pane;
import javafx.application.Platform;

public class Client{

    /**
     * booléen permettant de vérifier la connexion du client au serveur 
    */
    private boolean connected;
    /**
     * booléen permettant de vérifier l'authentification du client au serveur
    */
    private boolean authenticated;

    /**
     * adresse du serveur 
    */
    private String controller_adress;
    /**
     * timeslice du ping 
    */
    private int display_timeout_value;
    /**
     * id de la vue  
    */
    private String id;
    /**
     * chemin d'accès au image  
    */
    private String resources;

    /**
     * port d'écoute du serveur 
    */
    private int port;

    /**
     * Socket du serveur 
     */
    private Socket socket;
    /**
     * buffer de lecture des reponses du serveur
     */
    private BufferedReader in;
    /**
     * buffer d'écriture des reponses du serveur
     */
    private PrintWriter out;

    /**
     * liste de poissons gérés par la vue 
    */
    private ArrayList<Fish> fishList;

    /**
     * 
    */
    private BlockingQueue<String> listQueue = new LinkedBlockingDeque<>();

    /**
     * 
    */
    public BlockingQueue<String> consoleInPromptQueue = new LinkedBlockingDeque<>();

    /**
    * 
    */
    public BlockingQueue<String> consoleOutPromptQueue = new LinkedBlockingDeque<>();

    /**
    * 
    */
    private BlockingQueue<String> consoleQueue = new LinkedBlockingDeque<>();



    public Client(){
        config();
        handleConnection();
        fishList = new ArrayList<Fish>();

        Thread filterThread = new Thread(new Runnable() {
            @Override
            public void run() {
                 try {
                    while (true) {
                        while (connected && authenticated) {
                            try {                     
                                String msg = in.readLine();
                                System.out.println("Received "+ msg);
                                String[] tokens = msg.split(" ");

                                if(tokens[0].trim().equals("list")) {
                                    System.out.println("adding "+msg+" in list");
                                    listQueue.put(String.valueOf(msg));
                                }

                                if(tokens[0].equals("OK") || (tokens[0].equals("NOK")) || tokens[0].equals("Fish") || tokens[0].equals("bye")) {
                                    System.out.println("adding "+msg+" in consoleQueue");
                                    consoleQueue.put(String.valueOf(msg));
                                    break;
                                }

                            } catch (IOException e) {
                                System.out.println("Exception caught in filter thread");
                            }
                        }   
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        Thread pingThread = new Thread(new Runnable() {
            @Override
            public void run() {
                 try {
                    String msg = "ping 1234";
                    while (true) {
                        while (connected && authenticated) {
                            out.println(msg);
                            Thread.sleep(1000*display_timeout_value/2);
                        }   
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    
        Thread promptThread = new Thread(new Runnable() {
            @Override
            public void run() {
                 try {
                    while (true) {
                    {                   
                        String command = consoleInPromptQueue.take();
                        boolean send = sendConsoleCommand(command);
                        if(send){
                            String resp = consoleQueue.take();
                            try{
                                resp = handleConsoleCommand(command, resp);
                            } catch (InterruptedException e){
                                System.out.println("Error in handleConsoleCommand");
                            }
                            consoleOutPromptQueue.put(resp);
                        }
                        
                    }   
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        Thread getFishGoalThread = new Thread(new Runnable() {
            @Override
            public void run() {
                    while (true) {                      
                        while(authenticated && connected) {
                            try {
                                Thread.sleep(500);
                                for (Fish f : fishList){
                                    if(f.isRunning() && f.goals.size() < 2){
                                            out.println("ls");
                                        break;
                                    }
                                }
                            } catch (Exception e) {
                                e.printStackTrace();
                            }
                        }   
                    }
                
            }
        });

        Thread listThread = new Thread(new Runnable() {
            @Override
            public void run() {
                 try {
                    while (true) {
                        while (connected && authenticated) {
                            String list = listQueue.take();
                            if(list.equals("list ")) {
                                break;
                            }
                            ArrayList<String> lists = parseList(list);
                            for (String s : lists){
                                String[] infos = s.split(" ");
                                for(Fish f : fishList){
                                    if(f.getName().equals(infos[0]) && !f.goalsContains(Integer.parseInt(infos[1]), Integer.parseInt(infos[2]))){
                                        f.addGoal(new Goal(Integer.parseInt(infos[1]), Integer.parseInt(infos[2]), Integer.parseInt(infos[5])));
                                    }
                                }
                            }
                        }   
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        pingThread.start();
        filterThread.start();
        promptThread.start();
        listThread.start();
        getFishGoalThread.start();
    }

    /**
     * Récupérer les poissons gérés par les clients 
     */
    public ArrayList<Fish> getFishs() {
        return fishList;
    } 

    /*************************************************************************/
    /*                     SIDE FUNCTIONS                                   */
    /***********************************************************************/

    /**
     * Établissement de la connexion au serveur et envoie du message 
     * d'authentication
     */
    public void handleConnection(){
        try {
            socket = new Socket(controller_adress, port);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            out = new PrintWriter(socket.getOutputStream(),true);
            connected = true;
        } catch (IOException e) {
            connected = false;
        }
        out.println("hello in as "+id);
        String resp = null;
        try{
            resp = in.readLine();
        } catch(IOException e) {
            System.out.println("Error connecting");
        }
        if(resp.equals("greeting "+id)){
            authenticated = true;
        }
    }

     /**
     * configuration des variables relative à l'affichage 
     * via le fichier affichage.cfg
     */
    private void config() {
        try {
            List<String> lines = Files.readAllLines(Paths.get(System.getProperty("user.dir") + "/affichage.cfg"), StandardCharsets.ISO_8859_1);
            for (String s : lines) {
                if (!s.isEmpty()) {
                    String[] tokens = s.split(" ");
                    switch (tokens[0]) {
                        case "controller-address":
                            controller_adress = tokens[2];
                            break;
                        case "id":
                            id = tokens[2];
                            break;
                        case "controller-port":
                            port = Integer.parseInt(tokens[2]);
                            break;
                        case "display-timeout-value":
                            display_timeout_value = Integer.parseInt(tokens[2]);
                            break;
                        case "resources":
                            resources = tokens[2];
                            break;
                        default:
                            break;
                    }
                }
            }
        }catch (IOException e){
                System.out.println("Couldn't open affiche.cfg file");
        }
    }

    /**
     * Gestion des commandes de la console et envoie au serveur
     * @return response qui est un String pour la réponse du serveur
     */
    public boolean sendConsoleCommand(String inputConsole) throws InterruptedException{
        String[] args = inputConsole.split(" ");
        String response;

        switch (args[0]) {
            case "status":
                if (args.length == 1) {
                    out.println("status");
                    return true;
                } else {
                    consoleOutPromptQueue.put("<NOK. La commande 'status' ne prend aucun argument." + System.lineSeparator());
                    return false;
                }

            case "addFish":
                if (args.length == 5) {
                    Pattern pattern = Pattern.compile("^addFish\\s+(\\w+)\\s+at\\s+(\\d+)x(\\d+),(\\d+)x(\\d+),\\s*(\\w+)$");
                    Matcher matcher = pattern.matcher(inputConsole);

                    if (matcher.matches()) {
                        out.println(inputConsole);
                        return true;
                    }
                }
                consoleOutPromptQueue.put("<NOK. Usage: addFish 'nameFish' at 'x'x'y', 'w'x'h', 'mobilityModel'" + System.lineSeparator());
                return false;

            case "startFish":
                if (args.length == 2) {
                    Pattern pattern = Pattern.compile("^startFish\\s+\\S+");
                    Matcher matcher = pattern.matcher(inputConsole);

                    if (matcher.matches()) {
                        out.println(inputConsole);
                        return true;
                    } else {
                        consoleOutPromptQueue.put("<NOK. Usage: 'startFish nameFish'" + System.lineSeparator());
                    }
                } else {
                    consoleOutPromptQueue.put("<NOK. Usage: 'startFish nameFish'" + System.lineSeparator());
                }
                return false;

            case "delFish":
                if (args.length == 2) {
                    Pattern pattern = Pattern.compile("^delFish\\s+\\S+");
                    Matcher matcher = pattern.matcher(inputConsole);

                    if (matcher.matches()) {
                        out.println(inputConsole);
                        return true;
                    } else {
                        consoleOutPromptQueue.put("<NOK! Usage: 'delFish nameFish'" + System.lineSeparator());
                    }
                } else {
                    consoleOutPromptQueue.put("<NOK! Usage: 'delFish nameFish'" + System.lineSeparator());
                }
                return false;

            case "log":
                if(args.length == 2 && args[1].equals("out")){
                    out.println(inputConsole);
                    return true;
                }else {
                    consoleOutPromptQueue.put("<NOK! Usage: 'log out'" + System.lineSeparator());
                }
                return false;
            default:
                consoleOutPromptQueue.put("<NOK. Command not found." + System.lineSeparator());
                return false;
        }
    }


    private String handleConsoleCommand(String senderCommand, String serverResponse) throws InterruptedException {
        String[] command = senderCommand.split(" ");
        String[] response = serverResponse.split(" ");
        System.out.println("here with command "+command[0]);
        if(response[0].equals("OK")){
            switch(command[0]){
                case "addFish":
                    addFish(command);
                    return serverResponse;
                case "delFish":
                    delFish(command);
                    return serverResponse;
                case "startFish":
                    startFish(command);
                    return serverResponse;
                case "status":
                    System.out.println("send in status : "+ serverResponse);
                    String[] statusResp = serverResponse.split(" ");
                    int fishNb = Integer.parseInt(statusResp[5]);
                    String send = serverResponse;
                    for(int i=0; i < fishNb; i++){
                        send += "\t" + consoleQueue.take();
                    }
                    return send;
                default: return serverResponse;
            }
        }
        /*
        if(command[0].equals("ls") || command[0].equals("getFishesContinuously")){
            lsCommand(props.parsedFishList(response),props);
        }*/
        return serverResponse;
    }

    private void addFish(String[] command){
        String[] posInfo = command[3].split("x");
        int x = Integer.parseInt(posInfo[0]);
        int recty = Integer.parseInt(posInfo[2].replace(",",""));
        String[] posInfo2 = posInfo[1].split(",");
        int y = Integer.parseInt(posInfo2[0]);
        int rectx = Integer.parseInt(posInfo2[1]);
        Fish myFish = new Fish(command[1], x, y, rectx, recty); 
        fishList.add(myFish);
        Platform.runLater(() -> Main.addFish(myFish));
    }

    private void delFish(String[] command){
        ArrayList<Fish> newList = new ArrayList<>(fishList);
        for(Fish fish : newList){
            String fishName = fish.getName();
            if(fishName.equals(command[1])){
                if(fish.transi != null){
                    fish.transi.stop();
                }
                Platform.runLater(() -> Main.delFish(fish));
                fishList.remove(fish);
                break;
            }
        }
    }

    private void startFish(String[] command){
        for(Fish fish : fishList){
            String fishName = fish.getName();
            if(fishName.equals(command[1])){
                fish.start();
            }
        }
    }

    private String[] extractList(String str){
        String temp = str.substring(5, str.length()-1);
        String[] res = temp.split("]");
        for(int i=0;i <res.length;i++){
            res[i] = res[i].trim().substring(1,res[i].trim().length());
        }
        return res;
    }

    private ArrayList<String> parseList(String list) {
        String [] lists = extractList(list);
        ArrayList<String> res = new ArrayList<String>();
        for(String l : lists){
            if(!l.trim().equals("list")){
                String[] split = l.split(" ");
                String name = split[0];
                String[] infos = split[2].split(",");
                String time = infos[2];
                String[] posInfo = infos[0].split("x");
                String x = posInfo[0];
                String y = posInfo[1];
                String[] rectInfo = infos[1].split("x");
                String rectx = rectInfo[0];
                String recty = rectInfo[1];
                res.add( name + " "+ x+" " + y+" " + rectx+" " + recty+ " " + time);
            }
        }
        return res;
    }

    public void updateFishes(){
        for (Fish f : fishList){
            if(f.isRunning()){
                f.update();
            }
        }
    }
}
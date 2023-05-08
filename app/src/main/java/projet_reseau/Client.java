package projet_reseau;
import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javafx.scene.control.TextArea;
import java.util.Random;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.awt.geom.Point2D;

public class Client{
    
    /**
     * liste de poissons gérés par la vue 
    */
    private ArrayList<Fish> fishList;

    /**
     * port d'écoute du serveur 
    */
    private int port;

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
     * booléen permettant de vérifier la connexion du client au serveur 
    */
    private boolean connected;
    /**
     * booléen permettant de vérifier l'authentification du client au serveur
    */
    private boolean authenticated;
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
     * mutex pour l'écriture dans le socket du serveur
     */
    private Lock socketLock = new ReentrantLock();


    /**
     * constructeur ddu client 
     */
    public Client(){
        config();
        handleConnection();
        fishList = new ArrayList<Fish>();
        /**
        * thread pour le ping de connexion
        */ 
        Thread pingThread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    while (true) {
                        Thread.sleep(1000 * display_timeout_value/3);
                        while (!authenticated) {
                            Thread.sleep(5000);
                        }
                        if (!connected) {
                            break;
                        }
                        String pong = null;
                        try {
                            socketLock.lock();
                            out = new PrintWriter(socket.getOutputStream(),true);
                            out.println("ping 12345");
                            out.flush();
                            pong = in.readLine();
                        } catch (IOException e) {
                            System.out.println("Exception caught");
                        } finally {
                            socketLock.unlock();
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
          
        Thread getFishThread = new Thread(new Runnable(){
            @Override
            public void run() {
                try {
                    String commandeFish = "ls";
                    while (true) {
                        Thread.sleep(1000 * display_timeout_value);
                        send("ls");
                        if (!connected) {
                            break;
                        }
                        try {
                            if(commandeFish.equals("ls")) {
                                ArrayList<String> response = readLinesLs(in);
                                for(String line : response){
                                    System.out.println(line);
                                    whichCommand("ls", line);
                                }
                            }else if(commandeFish.equals("getfishcontinuously")) {
                                String response = in.readLine();
                                System.out.println(response);
                            }
                        } catch (IOException e) {
                            System.out.println("Exception caught");
                        }
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
        pingThread.start();
        getFishThread.start();
    }


    /*************************************************************************/
    /*                             GETTER                                   */
    /***********************************************************************/

    /**
     * Récupérer les poissons gérés par les clients 
     */
    public ArrayList<Fish> getFishs() {
        return fishList;
    }


    /*************************************************************************/
    /*                             SETTER                                   */
    /***********************************************************************/


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
            connected = true;
            out = new PrintWriter(socket.getOutputStream(),true);
        } catch (IOException e) {
            connected = false;
        }
        boolean bool = handleHello();
        if(bool){
            authenticated = true;
        }
    }

    public void close() throws IOException {
        socket.close();
        in.close();
        out.close();
    }

    /**
     * Gestion de la commande Hello pour l'authentification du client
     * auprès du serveur
     * @return true si l'authentification du client est réussie
     * @return false sinon 
     */
    public boolean handleHello(){
        String message = "hello in as " + id;
        send(message);
        try{
            String response = in.readLine();
            String numberStr = response.substring(response.indexOf("N") + 1);
            id = numberStr; 
            return true;
        }catch(IOException e){
                return false;
        }
    }

    /**
     * Fonction d'envoi des commandes au serveur 
     */
    public void send(String command) {
        if (socketIsConnected()) {
            try{
                socketLock.lock();
                out.println(command);
                out.flush();
            }finally{
                socketLock.unlock();
            }
        }
        if (command.equals("disconnect")) {
            connected = false;
            try{
                close();
            }catch(IOException e){
                System.out.println("Couldn't close");
            }
        }
        if (command.equals("log out")) {
            authenticated = false;
        }
    }

    /**
     * Fonction de vérification de la connexion du socket Serveur 
     */
    public boolean socketIsConnected() {
        return (socket != null && socket.isConnected());
    }

    /**
     * Gestion des commandes de la console et envoie au serveur
     * @return response qui est un String pour la réponse du serveur
     */
    public String handleCommand(String inputConsole) {
        String[] args = inputConsole.split(" ");
        String response;

        switch (args[0]) {
            case "status":
                if (args.length == 1) {
                    send(inputConsole);
                    try {
                        response = readLinesStatus(in);
                        return response;
                    } catch (IOException e) {
                        return "Exception: problème lors de la récupération de la réponse du serveur" + System.lineSeparator();
                    }
                } else {
                    return "<NOK. La commande 'status' ne prend aucun argument." + System.lineSeparator();
                }

            case "addFish":
                if (args.length == 5) {
                    Pattern pattern = Pattern.compile("^addFish\\s+(\\w+)\\s+at\\s+(\\d+)x(\\d+),(\\d+)x(\\d+),\\s*(\\w+)$");
                    Matcher matcher = pattern.matcher(inputConsole);

                    if (matcher.matches()) {
                        send(inputConsole);
                        try {
                            response = in.readLine();
                            System.out.println(response);
                            if(response != null && inputConsole != null) {
                                 whichCommand(inputConsole,response);
                            }
                            return response;
                        } catch (IOException e) {
                            return "Exception: problème lors de la récupération de la réponse du serveur" + System.lineSeparator();
                        }
                    }
                }

                return "<NOK. Usage: addFish 'nameFish' at 'x'x'y', 'w'x'h', 'mobilityModel'" + System.lineSeparator();

            case "startFish":
                if (args.length == 2) {
                    Pattern pattern = Pattern.compile("^startFish\\s+\\S+");
                    Matcher matcher = pattern.matcher(inputConsole);

                    if (matcher.matches()) {
                        System.out.println(inputConsole);
                        send(inputConsole);
                        try {
                            response = in.readLine();
                            if(response != null && inputConsole != null) {
                                 whichCommand(inputConsole,response);
                            }
                            return response;
                        } catch (IOException e) {
                            return "Exception: problème lors de la récupération de la réponse du serveur" + System.lineSeparator();
                        }
                    } else {
                        return "<NOK. Usage: 'startFish nameFish'" + System.lineSeparator();
                    }
                } else {
                    return "<NOK. Usage: 'startFish nameFish'" + System.lineSeparator();
                }

            case "delFish":
                if (args.length == 2) {
                    Pattern pattern = Pattern.compile("^delFish\\s+\\S+");
                    Matcher matcher = pattern.matcher(inputConsole);

                    if (matcher.matches()) {
                        send(inputConsole);
                        try {
                            response = in.readLine();
                            if(response != null && inputConsole != null) {
                                 whichCommand(inputConsole,response);
                            }
                            return response;
                        } catch (IOException e) {
                            return "Exception: problème lors de la récupération de la réponse du serveur" + System.lineSeparator();
                        }
                    } else {
                        return "<NOK! Usage: 'delFish nameFish'" + System.lineSeparator();
                    }
                } else {
                    return "<NOK! Usage: 'delFish nameFish'" + System.lineSeparator();
                }
            case "log":
                if(args.length == 2 && args[1].equals("out")){
                    send(inputConsole);
                    authenticated = false;
                    try{
                        response = in.readLine();
                        System.out.println(response);
                        return response;
                    }catch (IOException e){
                        return "Exception: problème lors de la récupération de la réponse du serveur" + System.lineSeparator();
                    }
                }else {
                    return "<NOK! Usage: 'log out'" + System.lineSeparator();
                }
            default:
                return "<NOK. Command not found." + System.lineSeparator();
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

    public void whichCommand(String senderCommand, String serverResponse){
        FishProperties props = new FishProperties(); 
        props.getStringServer(senderCommand, serverResponse); 

        String[] command = props.getCommand();
        String[] response = props.getResponse();  

        if(response[0].equals("OK")){
            switch(command[0]){
                case "addFish":
                    addFish(command, props.createSize(command), props.createPosition(command));
                    break;
                case "delFish":
                    delFish(command);
                    break;
                case "startFish":
                    startFish(command);
                    break;
                default: break;
            }
        }
        if(command[0].equals("ls")){
            lsCommand(props.parsedFishList(response),props);
        }
    }
    public void addFish(String[] command, Point2D size, Point2D position){
        Fish myFish = new Fish(command[1], position.getX(), position.getY(), size.getX(), size.getY()); 
        fishList.add(myFish);
    }

    public void delFish(String[] command){
        for(Fish fish : fishList){
            String fishName = fish.getName();
            if(fishName.equals(command[1])){
                fishList.remove(fish); 
            }
        }
    }

    public void startFish(String[] command){
        for(Fish fish : fishList){
            String fishName = fish.getName();
            if(fishName.equals(command[1])){
                fish.setRunning(true); 
            }
        }
    }

    private Fish findFish(String name){
        for(Fish fish : fishList){
            String fishName = fish.getName();
            if(fishName.equals(name)){
                return fish;
            }
        }
        return null; 
    }

    public String readLinesStatus(BufferedReader reader) throws IOException {
        StringBuilder builder = new StringBuilder();
        String line;
        boolean ignore = true;
        while ((line = reader.readLine()) != null) {
            if (line.contains("Connecté")) {
                ignore = false;
            }
            if (ignore) {
                continue;
            }
            if (!line.matches(".*\\d+.*")) {
                break;
            }
            builder.append(line);
        }
        return builder.toString();
    }

    public ArrayList<String> readLinesLs(BufferedReader reader) throws IOException {
        ArrayList<String> builder = new ArrayList<String>();
        String line;
        boolean ignore = true;
        while ((line = reader.readLine()) != null) {
            if (line.contains("list")) {
                ignore = false;
            }
            if (ignore) {
                continue;
            }
            if (!line.contains("list")) {
                break;
            }
            builder.add(line);
        }
        return builder;
    }

    public void lsCommand(ArrayList<String[]> fishes, FishProperties props){
        for(String[] strFish : fishes){
            System.out.println(strFish[0]);
            Fish fish = findFish(strFish[0]);
            Point2D position = props.createPosition(strFish);
            if(fish != null){
                fish.setGoalList(position);
                fish.setTime(Integer.parseInt(strFish[3]));
            }
            System.out.println("time" + Integer.parseInt(strFish[3]));
        }
    }

}
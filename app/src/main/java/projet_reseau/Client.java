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
    private boolean authentificated;
    /**
     * Socket du serveur 
     */
    private Socket socket;
    /**
     * buffer de lecture des reponses du serveur
     */
    protected BufferedReader in;
    

    public Client(){
        config();
        handleConnection();

        // thread pour le ping de connexion
        Thread pingThread = new Thread(new Runnable(){
            @Override
            public void run() {
                try {
                    while (true) {
                        Thread.sleep(1000 * display_timeout_value);
                        while (! authentificated) {
                            Thread.sleep(5000);
                        }
                        if (!connected) {
                            break;
                        }
                        String pong = null;
                        PrintWriter out =  new PrintWriter(socket.getOutputStream());
                        out.print("ping 12345");
                        out.flush();
                        pong = in.readLine();
                        if (!pong.equals("pong 12345")) {
                            authentificated = false;
                        }
                    }
                }
                catch (Exception e) {
                    e.printStackTrace();
                }       
            }
        });
        pingThread.start();
        fishList = new ArrayList<Fish>();
        Fish fish = new Fish("PoissonClown",30,90,10,10,100);
        fishList.add(fish);
        
        // je simule getFish dans le client  
        Thread getFishThread = new Thread(new Runnable(){
            @Override
            public void run() {
                while(true){
                    try{
                        Thread.sleep(1000*display_timeout_value);
                        Random rand = new Random();
                        double xg = rand.nextDouble(100);
                        double yg = rand.nextDouble(100);
                        fish.setGoal(xg,yg);
                    }catch(Exception e){
                        e.printStackTrace();
                    }
                }
            }
        });
        getFishThread.start();
    }

    public void handleConnection(){
        try {
            socket = new Socket(controller_adress, port);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            connected = true;
        } catch (IOException e) {
            connected = false;
        }
        int bool = handleHello();
        if(bool==1){
            authentificated = true;
        }
    }

    public int handleHello(){
        String message = "hello in as " + id;
        send(message);
        try{
            String response = in.readLine();
            String numberStr = response.substring(response.indexOf("N") + 1);
            id = numberStr; 
            return 1;
        }catch(IOException e){
                return 0;
        }
    }

    public void send(String s) {
        if (socketIsConnected()) {
            try {
                PrintWriter out =  new PrintWriter(socket.getOutputStream());
                out.println(s);
                out.flush();
            } catch (IOException e) {System.out.println("Exception caught");}
        }
        if (s.equals("disconnect")) {
            connected = false;
        }
        if (s.equals("log out")) {
            authentificated = false;
        }
    }

    public boolean socketIsConnected() {
        return (socket != null && socket.isConnected());
    }


    public String handleCommand(String inputConsole) {
        String[] args = inputConsole.split(" ");
        String response;

        switch (args[0]) {
            case "status":
                if (args.length == 1) {
                    send(inputConsole);
                    try {
                        response = in.readLine();
                        return response;
                    } catch (IOException e) {
                        return "<NOK. The command 'status' doesn't expect arguments." + System.lineSeparator();
                    }
                } else {
                    return "<NOK. The command 'status' doesn't expect arguments." + System.lineSeparator();
                }

            case "addFish":
                if (args.length == 5) {
                    Pattern pattern = Pattern.compile("^addFish\s+(\\w+)\\s+at\\s+(\\d+x\\d+)(?:,(\\d+x\\d+))?(?:,(\\w+))?$");
                    Matcher matcher = pattern.matcher(inputConsole);

                    if (true) {
                        send(inputConsole);
                        try {
                            response = in.readLine();
                            return response;
                        } catch (IOException e) {
                            return "<NOK. Usage: addFish 'nameFish' at 'x'x'y', 'w'x'h', 'mobilityModel'" + System.lineSeparator();
                        }
                    }
                }

                return "<NOK. Usage: addFish 'nameFish' at 'x'x'y', 'w'x'h', 'mobilityModel'" + System.lineSeparator();

            case "startFish":
                if (args.length == 2) {
                    Pattern pattern = Pattern.compile("^startFish\\s+\\S+");
                    Matcher matcher = pattern.matcher(inputConsole);

                    if (matcher.matches()) {
                        send(inputConsole);
                        try {
                            response = in.readLine();
                            return response;
                        } catch (IOException e) {
                            return "<NOK. Usage: 'startFish nameFish'" + System.lineSeparator();
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
                            return response;
                        } catch (IOException e) {
                            return "<NOK! Usage: 'delFish nameFish'" + System.lineSeparator();
                        }
                    } else {
                        return "<NOK! Usage: 'delFish nameFish'" + System.lineSeparator();
                    }
                } else {
                    return "<NOK! Usage: 'delFish nameFish'" + System.lineSeparator();
                }

            default:
                return "<NOK. Command not found." + System.lineSeparator();
        }
    }

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

    public ArrayList<Fish> getFishs() {
        return fishList;
    }
}
import java.io.*;
import java.net.*;
import java.lang.Thread;

public class test_afficheur {

    public static void main(String[] args) {
        String serverAddress = "localhost";
        int port = 5000;

        try {
            
            // Établissement de la connexion avec le serveur
            Socket socket = new Socket(serverAddress, port);

            OutputStream outputStream = null;
            PrintWriter writer = null;
            InputStream inputStream = null;
            BufferedReader reader = null;

             // Envoi du message de connexion au serveur
            outputStream = socket.getOutputStream();
            writer = new PrintWriter(outputStream, true);
            writer.println("hello in as N3");

            // Lecture de la réponse du serveur
            inputStream = socket.getInputStream();
            reader = new BufferedReader(new InputStreamReader(inputStream));
            String response = reader.readLine();
            System.out.println("Server response: " + response);

             // Envoi du message d'ajout d'un poisson
            outputStream = socket.getOutputStream();
            writer = new PrintWriter(outputStream, true);
            writer.println("getFishes");

            // Lecture de la réponse du serveur
            inputStream = socket.getInputStream();
            reader = new BufferedReader(new InputStreamReader(inputStream));
            response = reader.readLine();
            System.out.println("Server response: " + response);


            // Envoi du message d'ajout d'un poisson
            outputStream = socket.getOutputStream();
            writer = new PrintWriter(outputStream, true);
            writer.println("addFish CloWNFish at 40x30,10x3, RandomWaypoint");

            // Lecture de la réponse du serveur
            inputStream = socket.getInputStream();
            reader = new BufferedReader(new InputStreamReader(inputStream));
            response = reader.readLine();
            System.out.println("Server response: " + response);

            // Envoi du message d'ajout d'un poisson
            outputStream = socket.getOutputStream();
            writer = new PrintWriter(outputStream, true);
            writer.println("addFish ClownFish_3 at 40x30,10x3, RandomWaypoint");

            // Lecture de la réponse du serveur
            inputStream = socket.getInputStream();
            reader = new BufferedReader(new InputStreamReader(inputStream));
            response = reader.readLine();
            System.out.println("Server response: " + response);

            // Envoi du message d'ajout d'un poisson
            outputStream = socket.getOutputStream();
            writer = new PrintWriter(outputStream, true);
            writer.println("getFishes");

            // Lecture de la réponse du serveur
            inputStream = socket.getInputStream();
            reader = new BufferedReader(new InputStreamReader(inputStream));
            response = reader.readLine();
            System.out.println("Server response: " + response);

            // Envoi du message d'ajout d'un poisson
            outputStream = socket.getOutputStream();
            writer = new PrintWriter(outputStream, true);
            writer.println("delFish ClownFish_36");

            // Lecture de la réponse du serveur
            inputStream = socket.getInputStream();
            reader = new BufferedReader(new InputStreamReader(inputStream));
            response = reader.readLine();
            System.out.println("Server response: " + response);

            // Envoi du message démarrage d'un poisson
            outputStream = socket.getOutputStream();
            writer = new PrintWriter(outputStream, true);
            writer.println("startFish CloWNFish");

            // Lecture de la réponse du serveur
            inputStream = socket.getInputStream();
            reader = new BufferedReader(new InputStreamReader(inputStream));
            response = reader.readLine();
            System.out.println("Server response: " + response);
            
            
            for(int i=0; i<10;i++){
                

                // Envoi du message d'ajout d'un poisson
                outputStream = socket.getOutputStream();
                writer = new PrintWriter(outputStream, true);
                writer.println("getFishes");

                // Lecture de la réponse du serveur
                inputStream = socket.getInputStream();
                reader = new BufferedReader(new InputStreamReader(inputStream));
                response = reader.readLine();
                System.out.println("Server response: " + response);

                try{
                    Thread.sleep(1000);
                } catch(Exception e) {
           
                    // catching the exception
                    System.out.println(e);
                }
            }

            reader.close();
            outputStream.close();
            writer.close();
            inputStream.close();
            socket.close();
            
            
            
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
import java.io.*;
import java.net.*;
import java.lang.Thread;

public class test_afficheur {

    public static void main(String[] args) {
        String serverAddress = "localhost";
        int port = 3000;

        try {
            
            // Établissement de la connexion avec le serveur
            Socket socket = new Socket(serverAddress, port);

            OutputStream outputStream = socket.getOutputStream();
            InputStream inputStream = socket.getInputStream();
            PrintWriter writer = new PrintWriter(outputStream, true);
            BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));

            // Envoi du message de connexion au serveur
            writer.println("hello");

            // Lecture de la réponse du serveur       
            String response = reader.readLine();
            System.out.println("Server response: " + response);

             // Envoi du message d'ajout d'un poisson
            writer.println("ls");

            // Lecture de la réponse du serveur
            response = reader.readLine();
            System.out.println("Server response: " + response);


            // Envoi du message d'ajout d'un poisson
            writer.println("addFish ClownFish_0 at 40x30,10x3, RandomWaypoint");

            // Lecture de la réponse du serveur
            response = reader.readLine();
            System.out.println("Server response: " + response);

            // Envoi du message d'ajout d'un poisson
            writer.println("addFish ClownFish_1 at 70x30,10x3, RandomWaypoint");

            // Lecture de la réponse du serveur
            response = reader.readLine();
            System.out.println("Server response: " + response);

            // Envoi du message d'ajout d'un poisson
            writer.println("addFish ClownFish_2 at 40x30,10x3, RandomWaypoint");

            // Lecture de la réponse du serveur
            response = reader.readLine();
            System.out.println("Server response: " + response);

            // Envoi du message d'ajout d'un poisson
            outputStream = socket.getOutputStream();
            writer = new PrintWriter(outputStream, true);
            writer.println("ls");

            // Lecture de la réponse du serveur
            inputStream = socket.getInputStream();
            reader = new BufferedReader(new InputStreamReader(inputStream));
            response = reader.readLine();
            System.out.println("Server response: " + response);

            // Envoi du message démarrage d'un poisson
            outputStream = socket.getOutputStream();
            writer = new PrintWriter(outputStream, true);
            writer.println("startFish ClownFish_1");

            // Lecture de la réponse du serveur
            inputStream = socket.getInputStream();
            reader = new BufferedReader(new InputStreamReader(inputStream));
            response = reader.readLine();
            System.out.println("Server response: " + response);

             try{
                    Thread.sleep(2000);
                } catch(Exception e) {
           
                    // catching the exception
                    System.out.println(e);
                }


            // Envoi du message démarrage d'un poisson
            outputStream = socket.getOutputStream();
            writer = new PrintWriter(outputStream, true);
            writer.println("ls");



            /*
            for(int i=0; i<10;i++){
                

                // Envoi du message d'ajout d'un poisson
                outputStream = socket.getOutputStream();
                writer = new PrintWriter(outputStream, true);
                writer.println("ls");

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
            }*/

            while(true){
                // Lecture de la réponse du serveur
                inputStream = socket.getInputStream();
                reader = new BufferedReader(new InputStreamReader(inputStream));
                response = reader.readLine();
                System.out.println("Server response: " + response);
                if(response == null){
                    break;
                }
            }

            //Envoi du message de deconnection
            outputStream = socket.getOutputStream();
            writer = new PrintWriter(outputStream, true);
            writer.println("log out");

            // Lecture de la réponse du serveur
            inputStream = socket.getInputStream();
            reader = new BufferedReader(new InputStreamReader(inputStream));
            response = reader.readLine();
            System.out.println("Server response: " + response);

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
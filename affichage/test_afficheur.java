import java.io.*;
import java.net.*;

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
            
            for(int i=0; i<10;i++){
                

                // Envoi d'un message au serveur
                outputStream = socket.getOutputStream();
                writer = new PrintWriter(outputStream, true);
                writer.println("Message n"+i);

                // Lecture de la réponse du serveur
                inputStream = socket.getInputStream();
                reader = new BufferedReader(new InputStreamReader(inputStream));
                String response = reader.readLine();
                System.out.println("Server response: " + response);

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
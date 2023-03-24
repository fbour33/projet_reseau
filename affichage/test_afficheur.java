import java.io.*;
import java.net.*;

public class test_afficheur {

    public static void main(String[] args) {
        String serverAddress = "localhost";
        int port = 5000;

        try {
            // Établissement de la connexion avec le serveur
            Socket socket = new Socket(serverAddress, port);

            // Envoi d'un message au serveur
            OutputStream outputStream = socket.getOutputStream();
            PrintWriter writer = new PrintWriter(outputStream, true);
            writer.println("comment ca mon reuf");

            // Lecture de la réponse du serveur
            InputStream inputStream = socket.getInputStream();
            BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
            String response = reader.readLine();
            System.out.println("Server response: " + response);

            // Fermeture du socket et des flux d'entrée/sortie
            reader.close();
            writer.close();
            outputStream.close();
            inputStream.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
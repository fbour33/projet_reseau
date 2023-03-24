#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 5000

int main(int argc, char const *argv[]) {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    char buffer[1024] = {0};

    // Création du socket du serveur
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse du serveur
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Attache du socket à l'adresse du serveur
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Écoute des connexions entrantes
    if (listen(server_socket, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // Attente de connexion d'un client
    int address_length = sizeof(client_address);
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, (socklen_t*)&address_length)) < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // Lecture des données envoyées par le client
    int bytes_received = read(client_socket, buffer, 1024);
    printf("Received message: %s\n", buffer);

    // Envoi d'une réponse au client
    char *response = "Message received";
    int bytes_sent = send(client_socket, response, strlen(response), 0);
    printf("Response sent: %s\n", response);

    // Fermeture des sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
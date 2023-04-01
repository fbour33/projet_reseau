#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>

#include "server_handler.h"

#define MAX_CLIENTS 5

int main() {
	struct sockaddr cli;
	fd_set read_fds, active_fds;
	int sfd, cfd, connfd, max_sockfd;
	socklen_t len;
	int client_sockets[MAX_CLIENTS];
	for (int i = 0; i < MAX_CLIENTS; i++){
		client_sockets[i] = 0;
	}
	sfd = handle_bind();

	// initialize file descriptor sets
    FD_ZERO(&read_fds); // clear the set
    FD_SET(sfd, &read_fds); // add server socket to the set
    max_sockfd = sfd;


	if ((listen(sfd, SOMAXCONN)) != 0) {
		perror("listen()\n");
		exit(EXIT_FAILURE);
	}
	len = sizeof(cli);
	if ((connfd = accept(sfd, (struct sockaddr*) &cli, &len)) < 0) {
		perror("accept()\n");
		exit(EXIT_FAILURE);
	}

	char buff[MSG_LEN];
	while (1) {
		active_fds = read_fds;
		// Cleaning memory
		memset(buff, 0, MSG_LEN);

		// wait for activity on one of the sockets
        if (select(max_sockfd + 1, &active_fds, NULL, NULL, NULL) < 0) {
            perror("select failed");
            exit(EXIT_FAILURE);
        }

		 // check for activity on server socket
        if (FD_ISSET(sfd, &active_fds)) {
            socklen_t cli_len = sizeof(cli);
            // accept incoming connection
            if ((cfd = accept(sfd, (struct sockaddr *)&cli, &cli_len)) < 0) {
                perror("accept failed");
                exit(EXIT_FAILURE);
            }
            printf("New connection\n");

            // add client socket to the set
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = cfd;
                    break;
                }
            }
            FD_SET(cfd, &read_fds);

            if (cfd > max_sockfd) {
                max_sockfd = cfd;
            }
        }

		// check for activity on client sockets
        for (int i = 0; i < MAX_CLIENTS; i++) {
			if (FD_ISSET(client_sockets[i], &active_fds)) {
                // receive data from client
                if ((recv(client_sockets[i], buff, MSG_LEN, 0)) <= 0) {
                    // client disconnected
                    printf("Client disconnected, socket fd is %d\n", client_sockets[i]);
                    close(client_sockets[i]);
                    FD_CLR(client_sockets[i], &read_fds);
                    client_sockets[i] = 0;
                } else {
                    // print received data
                    printf("Received (socket fd %d): %s\n", client_sockets[i], buff);

                    // handle message and response
                    if (handle_message(buff, client_sockets[i]) == -1) {
						break;
					}
					printf("Message sent!\n");
                }
            }

		}
		
	}

	close(sfd);
	return EXIT_SUCCESS;
}
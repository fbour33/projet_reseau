#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/select.h>
#include <time.h>

#include "server_handler.h"
#include "../prompt/prompt.h"

#ifndef LOG_DIR
#define LOG_DIR "aled"
#endif

int main() {
	struct sockaddr cli;
	fd_set read_fds, active_fds, write_fds;
	int sfd, cfd, max_sockfd;

	//Load the config file
	parser_controller_config_file("controller.cfg", &controller_port, &display_timeout, &fish_update_interval);

	// Time handle
	time_t t0 = time(NULL);

	//storage for clients socket
	int client_sockets[MAX_CLIENTS];
	for (int i = 0; i < MAX_CLIENTS; i++){
		client_sockets[i] = -1;
		clients[i] = NULL;
	}

	//configure the server socket
	sfd = handle_bind();

	// initialize file descriptor sets
    FD_ZERO(&read_fds); // clear the set
    FD_SET(sfd, &read_fds); // add server socket to the set
	FD_SET(STDIN_FILENO, &read_fds); //add STDIN to the set (for prompt message)
    max_sockfd = sfd;

	//initialise le fichier log ou pas
	char log_dir[MSG_LEN] = LOG_DIR;
	log_f = init_log_f(log_dir);

	//Charge l'aquarium
	global_aquarium = create_aquarium();
	fprintf(log_f, "Loading aquarium ...\n");
	load_aquarium(global_aquarium);
	fprintf(log_f, "Aquarium loaded !\n");
	
	if ((listen(sfd, SOMAXCONN)) != 0) {
		fprintf(log_f, "listen() error\n");
		fflush(log_f);
		exit(EXIT_FAILURE);
	}

	char buff[MSG_LEN];
	printf(GREENBOLD"aquarium: $ ");
	fflush(STDIN_FILENO);
	// main loop
	while (1) {

		// time check for actualisation
		time_t tmp = time(NULL);
		int diff = difftime(tmp, t0);
		if(diff >= 1) {
			t += diff;
			//printf("%ld\n", t);
			if(update_fishes() == -1){
				fprintf(log_f, "Error updating fishes, exit\n");
				fflush(log_f);
				break;
			} 
			for(int i=0; i<MAX_CLIENTS; i++){
				if(clients[i] != NULL && clients[i]->last_getFishesContinuously_t != NO_GETFISHESCONTINUOUSLY){
					response_getFishesContinously(clients[i]->cfd);
				}
			}
			t0 = tmp;
		}

		active_fds = read_fds;
		write_fds = read_fds;
		// Cleaning memory
		memset(buff, 0, MSG_LEN);

		// wait for activity on one of the sockets
		struct timeval waiting_time;
		waiting_time.tv_sec = 0;
		waiting_time.tv_usec = 0;
        if (select(max_sockfd + 1, &active_fds, &write_fds, NULL, &waiting_time) < 0) {
            fprintf(log_f, "select failed, exit\n");
			fflush(log_f);
            break;
        }

		// check for activity on server socket
        if (FD_ISSET(sfd, &active_fds)) {
            socklen_t cli_len = sizeof(cli);
            // accept incoming connection
            if ((cfd = accept(sfd, (struct sockaddr *)&cli, &cli_len)) < 0) {
                fprintf(log_f, "accept failed\n");
				fflush(log_f);
                break;
            }
           fprintf(log_f, "New connection : socket %d\n", cfd);

            // add client socket to the set
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == -1) {
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
			if(client_sockets[i] != -1 && FD_ISSET(client_sockets[i], &write_fds)) {
				struct client *cli = get_cli_from_sock(client_sockets[i]);
				if(cli != NULL && t-cli->last_msg_t >= display_timeout){
					if (disconnect_client(client_sockets[i]) != 0){
							fprintf(log_f, "Can't disconnect the client, socket fd is %d, exit\n", client_sockets[i]);
							break;
					}
					else {
							fprintf(log_f, "Client timeout, socket fd is %d\n", client_sockets[i]);
							if (send(client_sockets[i], "bye\n", 5, 0) <= 0) {
								return -1;
							}
							FD_CLR(client_sockets[i], &read_fds);
							close(client_sockets[i]);
							client_sockets[i] = -1;
					}
				}
			}
			if (client_sockets[i] != -1 && FD_ISSET(client_sockets[i], &active_fds)) {
				memset(buff, 0, MSG_LEN);
                // receive data from client
                if ((recv(client_sockets[i], buff, MSG_LEN, MSG_DONTWAIT)) <= 0) {
                    // inactive socket
					if(is_client(client_sockets[i])){
						struct client *cli = get_cli_from_sock(client_sockets[i]);
						if(t-cli->last_msg_t >= display_timeout){
							if (disconnect_client(client_sockets[i]) != 0){
								fprintf(log_f, "Can't disconnect the client, socket fd is %d, exit\n", client_sockets[i]);
								break;
							}
							else {
								fprintf(log_f, "Client timeout, socket fd is %d\n", client_sockets[i]);
								if (send(client_sockets[i], "bye\n", 5, 0) <= 0) {
									return -1;
								}
								FD_CLR(client_sockets[i], &read_fds);
								close(client_sockets[i]);
								client_sockets[i] = -1;
							}
						}
					} else {
						fprintf(log_f, "Non-client socket fd %d disconnected\n", client_sockets[i]);
						FD_CLR(client_sockets[i], &read_fds);
						close(client_sockets[i]);
						client_sockets[i] = -1;
					}
					
                } else {
                    // print received data
                    fprintf(log_f, "Received (socket fd %d): %s", client_sockets[i], buff);

                    // handle message and response
                    if (handle_message(buff, client_sockets[i]) == -1) {
						fprintf(log_f, "handle_message of client message (socket : %d) error\n", client_sockets[i]);
						break;
					}
					fprintf(log_f, "Response sent!\n\n");
                }
            }

		}

		// check for activity on prompt (STDIN)
		if(FD_ISSET(STDIN_FILENO, &active_fds)) {
			memset(buff, 0, MSG_LEN);
			if(read(STDIN_FILENO, buff, MSG_LEN) == -1){
				fprintf(log_f, "read() failed\n");
			}
			fprintf(log_f, "received from prompt : %s", buff);
			int ret = handle_command_line(buff);
			if (ret == -1) {
				fprintf(log_f, "handle_command_line of prompt error\n");
			};
			if (ret == 1) {
				fprintf(log_f, "Exit the program\n");
				break;
			}
			printf(GREENBOLD"aquarium: $ ");
			fflush(STDIN_FILENO);
		}

		fflush(log_f);
	}

	if (global_aquarium != NULL){
		free_aquarium(global_aquarium);
	}
	for(int i=0; i < MAX_CLIENTS; i++){
		if(clients[i] != NULL){
			free_client(clients[i]);
		}
	}
	close(sfd);
	fclose(log_f);
	return EXIT_SUCCESS;
}
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>

#include "server_handler.h"
#include "../client/client.h"

int handle_bind() {
	struct addrinfo hints, *result, *rp;
	int sfd;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if (getaddrinfo(NULL, SERV_PORT, &hints, &result) != 0) {
		perror("getaddrinfo()");
		exit(EXIT_FAILURE);
	}
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype,
		rp->ai_protocol);
		if (sfd == -1) {
			continue;
		}
		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0) {
			break;
		}
		close(sfd);
	}
	if (rp == NULL) {
		fprintf(stderr, "Could not bind\n");
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(result);
	return sfd;
}

/**
 * @brief check if an id is valid 
 * @return 1 on success 0 on failure
 */
int is_valid_ID(char* id){
	if(strlen(id) <= 2){
		return 0;
	}
	if(id[0] == 'N') {
		for(int i =1; i< strlen(id)-1; i++){
			if(!isdigit(id[i])){
				return 0;
			}
		}
		if(id[strlen(id)-1] == '\n'){
			return 1;
		}
	}
	return 0;
}

/**
 * @brief function called when a hello message is received
 * @return 0 on success, -1 on failure
 */
int response_hello(int sockfd) {
	char *delim = " ";
    char *next = strtok(NULL, delim);
	if (next == NULL) {
		//attribuer un identifiant libre
		int view_id = linked_client(sockfd, -1);
		if(view_id == -1){
			if (send(sockfd, "no greeting\n", 13, 0) <= 0) {
				return -1;
			}
			return 0;
		}
		char msg[MSG_LEN];
		sprintf(msg, "greeting N%d\n", view_id);
		if (send(sockfd, msg, strlen(msg), 0) <= 0) {
				return -1;
		}
		return 0;
	}
	else if (strncmp(next, "in", 2) == 0 
			&& strncmp(strtok(NULL, delim), "as", 2) == 0){

		next = strtok(NULL, delim);
		if (is_valid_ID(next)) {
			//attribuer l'identifiant next au client
			linked_client(sockfd, atoi(next+1));
			char msg[MSG_LEN];
			sprintf(msg, "greeting %s\n", next);
			if (send(sockfd, msg, strlen(msg), 0) <= 0) {
					return -1;
			}
			return 0;
		}
		else {
			if (send(sockfd, "no greeting\n", 13, 0) <= 0) {
				return -1;
			}
		return 0;
		}
	}
	else {
		if (send(sockfd, "NOK\n", 5, 0) <= 0) {
			return -1;
		}
		return 0;
	}
	return -1;
}

int response_ping(int sockfd) {
	char *delim = " ";
    char *next = strtok(NULL, delim);
	if (next == NULL) {
		if (send(sockfd, "No value for ping\n", 19, 0) <= 0) {
				return -1;
		}
		return 0;
	}
	else {
		char resp[64] = "pong ";
		strcat(resp, next);
		strcat(resp, "\n");
		if (send(sockfd, resp, strlen(resp), 0) <= 0) {
				return -1;
		}
		return 0;
	}
	return -1;
}

/**
 * @brief Secondary function for handling the client message
 * @return 0 on success, -1 on failure
 */
int call_response(enum RESPONSE resp, int sockfd) {
	switch (resp) {
		case HELLO :
			return response_hello(sockfd);
		case PING :
			return response_ping(sockfd);
		default :
			return -1;
	}
}

/**
 * @brief function for handling the client message
 * @return 0 on success, -1 on failure
 */
int handle_message(char buffer[MSG_LEN], int sockfd) {
	char *token;
    char *delim = " ";
	token = strtok(buffer, delim);
	int is_cli = is_client(sockfd);

	if (token == NULL) {
		return 0;
	} else {
		if (strncmp(token, "hello", 5) == 0 && !is_cli) {
			return call_response(HELLO, sockfd);
		}
		if (strncmp(token, "ping", 4) == 0 && is_cli) {
			return call_response(PING, sockfd);
		}
		else {
			if (send(sockfd, "NOK\n", 5, 0) <= 0) {
				return -1;
			}
		}
	}
	return 0;
}

void echo_server(int sockfd) {
	char buff[MSG_LEN];
	while (1) {
		// Cleaning memory
		memset(buff, 0, MSG_LEN);
		// Receiving message
		if (recv(sockfd, buff, MSG_LEN, 0) <= 0) {
			break;
		}
		printf("Received: %s", buff);
		if (handle_message(buff, sockfd) == -1) {
			break;
		}
		printf("Message sent!\n");
	}
}        

FILE* init_log_f(char* log_dir) {
	FILE *fp;

	strcat(log_dir, "/log.txt");
    fp = fopen(log_dir, "w"); // ouvrir le fichier en mode écriture pour l'effacer
    fclose(fp);

    fp = fopen(log_dir, "a"); // ouvrir le fichier en mode ajout
    if (fp == NULL) {
        perror("fopen() failled");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "------ LOGS ------ \n");
	fflush(fp);

    return fp;
}
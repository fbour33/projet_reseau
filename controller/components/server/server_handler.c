#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server_handler.h"

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
 * @brief temporary function to check if an idea is valid 
 * @return 1
 */
int is_valid_ID(char* msg){
	return 1;
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
		if (send(sockfd, "greeting N**\n", 14, 0) <= 0) {
				return -1;
		}
		return 0;
	}
	else if (strncmp(next, "in", 2) == 0 
			&& strncmp(strtok(NULL, delim), "as", 2) == 0){

		next = strtok(NULL, delim);
		if (is_valid_ID(next)) {
			//attribuer l'identifiant next au client
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

/**
 * @brief Secondary function for handling the client message
 * @return 0 on success, -1 on failure
 */
int call_response(enum RESPONSE resp, int sockfd) {
	switch (resp) {
		case HELLO :
			return response_hello(sockfd); 
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

	if (token == NULL) {
		return 0;
	} else {
		if (strncmp(token, "hello", 5) == 0) {
			return call_response(HELLO, sockfd);
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
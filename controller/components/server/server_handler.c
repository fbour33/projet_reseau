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
		if (is_valid_ID(next) && linked_client(sockfd, atoi(next+1)) != -1) {//attribuer l'identifiant next au client
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

int response_getFishes(int sockfd){
	char *delim = " ";
    if (strtok(NULL, delim) != NULL){
		return -1;
	}
	struct client* cli = get_cli_from_sock(sockfd);
	char resp[1024];
	get_fishes(global_aquarium->aquarium_views[cli->view_idx], resp);
	if (send(sockfd, resp, strlen(resp), 0) <= 0) {
				return -1;
	}
	return 0;
}

int response_ls(int sockfd){
	return 0;
}

int response_getFishesContinously(int sockfd){
	return 0;
}

int response_addFish(int sockfd){
	char *delim = " ";
    char *name = strtok(NULL, delim);
	if(strcmp(strtok(NULL, delim), "at") != 0){
		if (send(sockfd, "NOK\n", 5, 0) <= 0) {
			return -1;
		}
		return 0;
	}
	delim = "x";
	char* x = strtok(NULL, delim);
	delim=",";
	char* y = strtok(NULL, delim);
	delim="x";
	char* w = strtok(NULL,delim);
	delim=",";
	char* h = strtok(NULL, delim);
	if(!is_number(x) || !is_number(y) || !is_number(w) || !is_number(h)){
		if (send(sockfd, "NOK\n", 5, 0) <= 0) {
			return -1;
		}
		return 0;
	}
	delim = " ";
	char *move = strtok(NULL, delim);
	move[strlen(move)-1] = '\0';
	enum STRATEGY strat = string_to_strategy(move);
	if(strat == UNREGISTERED){
		if (send(sockfd, "NOK : Modèle non supporté\n", 29, 0) <= 0) {
			return -1;
		}
		return 0;
	}

	delim = "_";
	char tmp[32];
	strcpy(tmp, name);
	char *type_str = strtok(tmp, delim);
	enum FISH_TYPE type = string_to_fish_type(type_str);
	if(type == INVALID){
		if (send(sockfd, "NOK\n", 5, 0) <= 0) {
			return -1;
		}
		return 0;
	}

	struct fish* new = create_fish(name, type, strat, atoi(x), atoi(y), atoi(w), atoi(h));
	struct client* cli = get_cli_from_sock(sockfd);
	if(add_fish(global_aquarium->aquarium_views[cli->view_idx], new) == -1){
		free_fish(new);
		if (send(sockfd, "NOK\n", 5, 0) <= 0) {
			return -1;
		}
		return 0;
	}
	if (send(sockfd, "OK\n", 4, 0) <= 0) {
			return -1;
	}
	return 0;
}

int response_delFish(int sockfd){
	char *delim = " ";
    char *name = strtok(NULL, delim);
	name[strlen(name)-1] = '\0';
	struct client* cli = get_cli_from_sock(sockfd);
	if(delete_fish(global_aquarium->aquarium_views[cli->view_idx], name) == -1){
		if (send(sockfd, "NOK\n", 5, 0) <= 0) {
			return -1;
		}
		return 0;
	}
	if (send(sockfd, "OK\n", 4, 0) <= 0) {
			return -1;
	}
	return 0;
}

int response_startFish(int sockfd){
	return 0;
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
		case GETFISHES :
			return response_getFishes(sockfd);
		case LS :
			return response_ls(sockfd);
		case GETFISHESCONTINOUSLY :
			return response_getFishesContinously(sockfd);
		case ADDFISH :
			return response_addFish(sockfd);
		case DELFISH :
			return response_delFish(sockfd);
		case STARTFISH :
			return response_startFish(sockfd);
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

	if (token != NULL) {
		if (!is_cli && strncmp(token, "hello", 5) == 0) {
			return call_response(HELLO, sockfd);
		}
		if (is_cli && strncmp(token, "ping", 4) == 0) {
			return call_response(PING, sockfd);
		}
		if (is_cli && strncmp(token, "getFishes", 9) == 0){
			return call_response(GETFISHES, sockfd);
		}
		if (is_cli && strncmp(token, "ls", 2) == 0){
			return call_response(LS, sockfd);
		}
		if (is_cli && strncmp(token, "getFishesContinuously", 21) == 0 ){
			return call_response(GETFISHESCONTINOUSLY, sockfd);
		}
		if (is_cli && strncmp(token, "addFish", 7) == 0 ){
			return call_response(ADDFISH, sockfd);
		}
		if (is_cli && strncmp(token, "delFish", 7) == 0 ){
			return call_response(DELFISH, sockfd);
		}
		if (is_cli && strncmp(token, "startFish", 9) == 0 ){
			return call_response(STARTFISH, sockfd);
		}
	}
	if (send(sockfd, "NOK\n", 5, 0) <= 0) {
		return -1;
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
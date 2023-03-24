#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "server_handler.h"

int main() {
	struct sockaddr cli;
	int sfd, connfd;
	socklen_t len;
	sfd = handle_bind();
	if ((listen(sfd, SOMAXCONN)) != 0) {
		perror("listen()\n");
		exit(EXIT_FAILURE);
	}
	len = sizeof(cli);
	if ((connfd = accept(sfd, (struct sockaddr*) &cli, &len)) < 0) {
		perror("accept()\n");
		exit(EXIT_FAILURE);
	}
	echo_server(connfd);
	close(sfd);
	return EXIT_SUCCESS;
}
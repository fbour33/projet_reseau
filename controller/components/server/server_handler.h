#ifndef SERVER_HANDLER
    #define SERVER_HANDLER
    
    #include <stdio.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <netinet/in.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #include <ctype.h>
    #include "../client/client.h"

    #define MSG_LEN 1024
    #define SERV_PORT "5000"
    #define SERV_ADDR "localhost"

    enum RESPONSE {
        HELLO, PING, ADDFISH, DELFISH, STARTFISH, GETFISHES, LS, GETFISHESCONTINOUSLY
    };

    void echo_server(int sockfd);

    int handle_bind();

    int handle_message(char buffer[MSG_LEN], int sockfd);

    /**
 * @brief Clean and open the log file 
 * @return the log file descriptor
 */
    FILE* init_log_f(char* log_dir);

#endif
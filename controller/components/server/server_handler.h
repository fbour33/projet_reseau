#ifndef SERVER_HANDLER
    #define SERVER_HANDLER


    #include<fcntl.h>
    #include <errno.h>

    #include "../client/client.h"
    #include "../../parser/parser.h"

    #define MSG_LEN 1024
    #define SERV_ADDR "localhost"

    void echo_server(int sockfd);

    int handle_bind();

    int handle_message(char buffer[MSG_LEN], int sockfd);

    int response_getFishesContinously(int sockfd);

    /**
    * @brief Clean and open the log file 
    * @return the log file descriptor
    */
    FILE* init_log_f(char* log_dir);

#endif
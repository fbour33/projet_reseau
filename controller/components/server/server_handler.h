#ifndef SERVER_HANDLER
    #define SERVER_HANDLER

    #include "../client/client.h"
    #include "../../parser/parser.h"

    #define MSG_LEN 1024
    #define SERV_PORT "5000"
    #define SERV_ADDR "localhost"

    unsigned long t;

    enum RESPONSE {
        HELLO, PING, ADDFISH, DELFISH, STARTFISH, GETFISHES, LS, GETFISHESCONTINOUSLY, LOGOUT
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
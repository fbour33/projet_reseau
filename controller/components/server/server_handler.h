#ifndef SERVER_HANDLER
    #define SERVER_HANDLER

    #define MSG_LEN 1024
    #define SERV_PORT "5000"
    #define SERV_ADDR "localhost"

    enum RESPONSE {
        HELLO
    };

    void echo_server(int sockfd);

    int handle_bind();

    int handle_message(char buffer[MSG_LEN], int sockfd);

    FILE* init_log_f(char* log_dir);

#endif
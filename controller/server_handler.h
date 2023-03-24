#ifndef SERVER_HANDLER
    #define SERVER_HANDLER

    #define MSG_LEN 1024
    #define SERV_PORT "5000"
    #define SERV_ADDR "localhost"

    void echo_server(int sockfd);

    int handle_bind();

#endif
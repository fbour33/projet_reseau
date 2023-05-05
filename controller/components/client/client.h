#ifndef CLIENT_H
#define CLIENT_H

#include "../aquarium/aquarium.h"

#define NO_GETFISHESCONTINUOUSLY 4294967295

struct client{
    int cfd;
    int view_idx;
    size_t last_msg_t;
    size_t last_getFishesContinuously_t;
    int getFishesContinuously_current_waypoint;
};

extern struct client* clients[MAX_CLIENTS];

/**
 * @brief Create a client
 */
struct client* create_client(int cfd, int view_idx);

/**
 * @brief Free a client 
 */
void free_client(struct client* client);

/**
 * @brief Disconnect a client based on his socket file descriptor and free the client
 * @return 0 on success, -1 on failure
 */
int disconnect_client(int cfd);

/**
 * @brief Create a client and add it to the clients array if it's possible
 * @return 0 on success, -1 on failure
 */
int linked_client(int cfd, int view_id);

/**
 * @brief Check if a socket is linked with a client
 * @return boolean : 1 on success, 0 on failure
 */
int is_client(int cfd);

/**
 * @brief Get the client pointer from the client socket
 * @return client pointer on success, NULL on failure
 */
struct client* get_cli_from_sock(int sockfd);

#endif
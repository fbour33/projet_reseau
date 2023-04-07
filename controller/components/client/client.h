#ifndef CLIENT_H
#define CLIENT_H

struct client{
    int cfd;
    int view_id;    
};

struct client* create_client(int cfd, int view_id);

void free_client(struct client* client);

#endif
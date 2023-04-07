#include <stdlib.h>
#include "client.h"

struct client* create_client(int cfd, int view_id){
    struct client *cli = malloc(sizeof(struct client));
    cli->cfd = cfd;
    cli->view_id = view_id;
    return cli;
}   

void free_client(struct client* client){
    free(client);
}
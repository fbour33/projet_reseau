#include "client.h"

struct client* clients[MAX_CLIENTS];

struct client* create_client(int cfd, int view_idx){
    struct client *cli = malloc(sizeof(struct client));
    cli->cfd = cfd;
    cli->view_idx = view_idx;
    return cli;
}   

void free_client(struct client* client){
    free(client);
}

int disconnect_client(int cfd){
    for(int i=0; i<MAX_CLIENTS; i++){
        if (NULL != clients[i] && clients[i]->cfd == cfd){
            global_aquarium->aquarium_views[clients[i]->view_idx]->free = 1;
            for(int j = 0; j <= global_aquarium->aquarium_views[clients[i]->view_idx]->nb_fishes; j++){
                free_fish(global_aquarium->aquarium_views[clients[i]->view_idx]->fishes[j]);
                global_aquarium->aquarium_views[clients[i]->view_idx]->fishes[j] = NULL;
            }
            free(clients[i]);
            clients[i] = NULL;
            return 0;
        }
    }
    return -1;
}

int is_client(int cfd){
    for(int i=0; i<MAX_CLIENTS; i++){
        if (clients[i]!= NULL && clients[i]->cfd == cfd){
            return 1; 
        }
    }
    return 0;
}

int linked_client(int cfd, int view_id){
    int view_idx = -1;
    if(view_id == -1){
        for(int i=0; i < MAX_CLIENTS;i++){
            if(global_aquarium->aquarium_views[i]->free == 1) {
                view_id = global_aquarium->aquarium_views[i]->id;
                view_idx = i;
                break;
            }
        }
        if(view_id == -1){
            return -1;
        }
    }
    if(global_aquarium->aquarium_views[view_idx]->free == 0){
        return -1;  
    }

    struct client* cli = create_client(cfd, view_idx);
    int ok = -1;
    for(int i=0; i<MAX_CLIENTS; i++){
        if(clients[i] == NULL){
            clients[i] = cli;
            ok = view_id;
            break;
        }
    }
    global_aquarium->aquarium_views[view_idx]->free = 0;
    return ok;
}

struct client* get_cli_from_sock(int sockfd){
    for(int i=0; i <MAX_CLIENTS; i++){
        if (clients[i] != NULL && clients[i]->cfd == sockfd){
            return clients[i];
        }
    }
    return NULL;
}
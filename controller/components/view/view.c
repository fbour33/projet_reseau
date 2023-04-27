#include "view.h"

struct view *create_view(int id, int x, int y, int width, int height){
    struct view * view = malloc(sizeof(struct view));

    view->id = id;
    view->p.x = x;
    view->p.y = y;
    view->d.width = width;
    view->d.height = height;
    view->free = 1; //1 if free 0 if not
    view->nb_fishes = 0;
    for(int i=0; i<MAX_FISHES; i++){
        view->fishes[i] = NULL;
    }
    return view;
}

int add_fish(struct view* view, struct fish* fish) {
    if (view->nb_fishes == MAX_FISHES-1) {
        //printf("There is no more space in this aquarium !\n");
        return -1;
    }
    if (fish_already_exists(fish)){
        //printf("Fish %s already exists!\n", fish->name);
        return -1;
    }
    view->fishes[view->nb_fishes] = fish;
    view->nb_fishes++;
    return 0;
}

// the fish is overwrited
int delete_fish(struct view* view, char* name){
    int index = -1;
    for(int i=0; i<view->nb_fishes; i++){
        if (strcmp(view->fishes[i]->name, name) == 0){
            index=i;
            break;
        }
    }
    if(index == -1) {
        //printf("\t-> Fish doesn't exist\n");
        return -1;
    }
    free_fish(view->fishes[index]);
    view->fishes[index] = NULL;
    for(int i=index;i<MAX_FISHES-1; i++){
        if(view->fishes[i+1] != NULL && view->fishes[i] == NULL){
            view->fishes[i] = view->fishes[i+1];
            view->fishes[i+1] = NULL;
        }
    }
    view->nb_fishes--;
    return 0;
}

int get_fishes(struct view* view, char *resp) {
    char msg[1024] = "list ";
    for(int i = 0; i< view->nb_fishes; i++) {
        struct fish* tmp = view->fishes[i];
        char temp[64];
        int time = 0;
        int posx = tmp->position.x;
        int posy = tmp->position.y;
        if(tmp->running){
            time = tmp->waypoints[0]->time_left;
            posx = tmp->waypoints[0]->pos.x;
            posy = tmp->waypoints[0]->pos.y;
        }
        sprintf(temp, "[%s at %dx%d,%dx%d,%d] ", tmp->name, posx, posy, 
                tmp->rectangle.width, tmp->rectangle.height, time);
        strcat(msg, temp);
    }
    strcat(msg, "\n");
    strcpy(resp, msg);
    return 0;
}

int status(struct view* view) {
    if(view->nb_fishes ==0) {
        return -1;
    }

    printf("\tOK : Connecté au contrôleur, %d poissons trouvés\n", view->nb_fishes);
    for(int i = 0; i<view->nb_fishes; ++i) {
        struct fish* tmp = view->fishes[i];
        printf("\n");
        printf("Fish %s at %d*%d,%d*%d", tmp->name, tmp->position.x, tmp->position.y, 
                tmp->rectangle.width, tmp->rectangle.height);
    }
    return 0;
}

void free_view(struct view* view) {
    for(int i = 0; i < MAX_FISHES; ++i) {
        if(view->fishes[i] != NULL){
            free_fish(view->fishes[i]);
        }
    }
    free(view);
}
#include "view.h"

struct view *create_view(int id, int x, int y, int width, int height){
    struct view * view = malloc(sizeof(struct view));

    view->id = id;
    view->p.x = x;
    view->p.y = y;
    view->d.width = width;
    view->d.height = height;
    view->free = 1; //1 if free 0 if not
    return view;
    view->nb_fishes = 0;
    return view;
}

int add_fish(struct view* view, struct fish* fish) {
    if (view->nb_fishes == MAX_FISHES-1) {
        printf("There is no more space in this aquarium !\n");
        return -1;
    }
    view->fishes[view->nb_fishes] = fish;
    view->nb_fishes++;
    return 0;
}

// the fish is overwrited
int delete_fish(struct view* view, char* name){
    int status = 0;
    int index = 0;
    for(int i=0; i<view->nb_fishes; i++){
        if (strncmp(view->fishes[index]->name, name, strlen(name)) == 0){
            index=i;
            status++;
            break;
        }
    }

    if(status == 0) {
        // printf("\t-> Your id doesn't exist\n");
        return -1;
    }
    free_fish(view->fishes[index]);
    for(int i=index;i<MAX_FISHES-1; i++){
        view->fishes[i]=view->fishes[i+1];
    }
    view->nb_fishes--;
    printf("\t-> view N%d deleted\n",status);
    return 0;
}

char* get_fishes(struct view* view, char *resp) {
    char msg[1024] = "list ";
    for(int i = 0; i< view->nb_fishes; ++i) {
        struct fish* tmp = view->fishes[i];
        // vérifier les paramètres car je ne savais quoi mettre ni dans quel ordre
        sprintf(msg, "[%s at %d*%d, %d*%d] ", tmp->name, tmp->position.x, tmp->position.y, 
                tmp->rectangle.width, tmp->rectangle.height);
    }
    strcat(msg, "\n");
    strcpy(resp, msg);
    return resp;
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
    for(int i = 0; i < view->nb_fishes; ++i) {
        free_fish(view->fishes[i]);
    }
    free(view);
}
#include "view.h"

struct view *create_view(int id, int x, int y, int width, int height){
    struct view * view = malloc(sizeof(struct view));

    view->id = id;
    view->p = _position(x,y);
    view->d.width = width;
    view->d.height = height;
    view->free = 1; //1 if free 0 if not
    for (int i = 0; i < MAX_FISHES; i++) {
        view->fishes[i] = malloc(sizeof(struct fish));
    }
}

int add_fish(struct view* view, struct fish* fish) {
    int index = 0;
    while(view->fishes[index] != NULL) {
        index ++;
    }
    if (index >= MAX_FISHES) {
        printf("There is no more space in this aquarium !\n");
        return -1;
    }
    view->fishes[index] = fish;
    return 0;
}

int delete_fish(struct view* view, char* name){
    int status = 0;
    int index = 0;
    for(int i=0; i<MAX_FISHES; i++){
        if (strncmp(view->fishes[index]->name, name, strlen(name))){
            index=i;
            status++;
            break;
        }
    }

    if(status == 0) {
        printf("\t-> Your id doesn't exist\n");
        return -1;
    }
    free(view->fishes[index]);
    for(int i=index;i<MAX_FISHES-1; i++){
        view->fishes[i]=view->fishes[i+1];
    }
    struct fish *fish = malloc(sizeof(struct fish));
    view->fishes[MAX_FISHES-1]= fish;
    printf("\t-> view N%d deleted\n",status);
}

struct fish* get_fishes(struct view* view) {
    int index = 0;
    printf("list ");
    while(view->fishes[index] != NULL) {
        struct fish* tmp = view->fishes[index];
        // vérifier les paramètres car je ne savais quoi mettre ni dans quel ordre
        printf("[%s at %d*%d, %d*%d] ", tmp->name, tmp->position.x, tmp->position.y, 
                tmp->rectangle.width, tmp->rectangle.height);
        ++index;
    }
    return view->fishes;
}

void status(struct view* view) {
    // vérifier qu'on est connécter en premier !
    int cpt = 0;
    while(view->fishes[cpt] != NULL) {
        ++cpt;
    }
    printf("\tOK : Connecté au contrôleur, %d poissons trouvés\n", cpt);
    for(int i = 0; i<cpt; ++i) {
        struct fish tmp = view->fishes[i];
        printf("\n");
        printf("Fish %s at %d*%d,%d*%d\n", tmp->name, tmp->position.x, tmp->position.y, 
                tmp->rectangle.width, tmp->rectangle.height);
    }
}

void free_view(struct view* view) {
    for(int i = 0; i < MAX_FISHES; ++i) {
        if (view->fishes[i] != NULL) {
            free(view->fishes[i]);
        }
    }
    free(view);
}
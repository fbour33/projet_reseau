#include <stdlib.h>
#include <string.h>
#include "fish.h"


struct fish * create_fish(char * name,enum FISH_TYPE fish_type,enum STRATEGY strategy,int x,int y,int width,int height){
    
    struct fish * fish= malloc(sizeof(struct fish));
    
    fish->name = malloc(strlen(name) + 1); // Allouer de la mémoire pour la chaîne de caractères
    strcpy(fish->name,name);
    fish->strategy=strategy;
    fish->type=fish_type;
    fish->position=_position(x,y);
    fish->rectangle.width=width;
    fish->rectangle.height=height;

    return fish;
}

void free_fish(struct fish *fish){
    free(fish);
}
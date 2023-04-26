#include <stdlib.h>
#include <string.h>
#include "fish.h"


struct fish * create_fish(char * name,enum FISH_TYPE fish_type,enum STRATEGY strategy,int x,int y,int width,int height){
    
    struct fish * fish= malloc(sizeof(struct fish));
    
    fish->name = malloc(32*sizeof(char));
    strcpy(fish->name,name);
    fish->strategy=strategy;
    fish->type=fish_type;
    fish->position.x=x;
    fish->position.y=y;
    fish->rectangle.width=width;
    fish->rectangle.height=height;
    fish->running = 0;

    return fish;
}

void free_fish(struct fish *fish){
    if(fish != NULL){
        free(fish->name);
        free(fish);
    }
}

enum FISH_TYPE string_to_fish_type(char* str){
    if(strcasecmp(str, "RedFish") == 0){
        return REDFISH;
    }
    if(strcasecmp(str,"Clownfish") == 0){
        return CLOWNFISH;
    }
    return INVALID;
}

enum STRATEGY string_to_strategy(char* str){
    if(strcasecmp(str, "Vertical") == 0){
        return VERTICAL;
    }
    if(strcasecmp(str, "Horizontal") == 0){
        return HORIZONTAL;
    }
    if(strcasecmp(str, "RandomWayPoint") == 0){
        return RANDOMWAYPOINT;
    }
    return UNREGISTERED;
}
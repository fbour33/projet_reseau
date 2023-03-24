#include "fish.h"
#include <string.h>

struct fish * create_fish(char * name,enum FISH_TYPE fish_type,enum STRATEGY strategy,int x,int y,int width,int height){
    struct fish * fish= malloc(sizeof(struct fish));

    fish->name=name;
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
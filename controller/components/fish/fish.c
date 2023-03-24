#include "fish.h"
#include <string.h>

struct fish * create_fish(enum FISH_TYPE fish_type,enum STRATEGY strategy,int x_start,int y_start,int x_final,int y_final){
    struct fish * fish= malloc(sizeof(struct fish));

    fish->strategy=strategy;
    fish->type=fish_type;
    fish->start_position=_position(x_start,y_start);
    fish->final_position=_position(x_final,y_final);

    return fish;
}

void free_fish(struct fish *fish){
    free(fish);
}
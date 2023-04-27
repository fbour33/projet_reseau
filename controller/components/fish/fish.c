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
    fish->wps_nb = 0;
    for(int i=0; i<MAX_WAYPOINT;i++){
        fish->waypoints[i] = NULL;
    }

    return fish;
}

void free_fish(struct fish *fish){
    if(fish != NULL){
        free(fish->name);
        for(int i=0; i<MAX_WAYPOINT; i++){
            if(fish->waypoints[i] != NULL){
                free(fish->waypoints[i]);
            }
        }
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

struct waypoint *create_waypoint(int x, int y, int time){
    struct waypoint *wp = malloc(sizeof(struct waypoint));
    wp->pos.x = x;
    wp->pos.y = y;
    wp->time_left = time;
    wp->total_time = time;
    return wp;
}

int RandomWayPoint(struct fish *fish){
    for(int i=0; i<MAX_WAYPOINT; i++){
        if(fish->waypoints[i] == NULL){
            struct waypoint *wp = create_waypoint(rand()%101, rand()%101, rand()%10);
            fish->waypoints[i] = wp;
            fish->wps_nb +=1;
            return 0;
        }
    }
    return -1;
}

int run(struct fish* fish){
    switch (fish->strategy){
    case RANDOMWAYPOINT:
        if(fish->wps_nb < 3) {
            RandomWayPoint(fish);
        }
        return 0;
    case HORIZONTAL :
        return 0;
    case VERTICAL :
        return 0;
    default:
        return -1;
    }
}
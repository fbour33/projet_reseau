#include <string.h>
#include "strategy.h"

enum STRATEGY get_strategy_from_string(char *strategy){
    if(strcmp(strategy,"RandomWayPoint")==0){
        return RANDOM;
    }else if(strcmp(strategy,"HorizontalWayPoint")==0){
        return HORIZONTAL;
    }else if(strcmp(strategy,"VerticalWayPoint")==0){
        return VERTICAL;
    }else{
        return UNREGISTERED;
    }
}
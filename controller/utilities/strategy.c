#include <string.h>
#include "strategy.h"

/**
 * @brief           convert a string value of a strategy get from the client to a enum value 
 * @param strategy  the string strategy to use for the fish get from the client
 */
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

/**
 * @brief    implement fish random move strategy
 * @param fish the string strategy to use for the fish get from the client
 */
void RandomWayPoint(struct fish *fish){
    
}
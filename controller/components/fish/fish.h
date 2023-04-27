#ifndef AQUARIUM_FISH_H
#define AQUARIUM_FISH_H

#include "../../utilities/tools.h"

#define MAX_FISHES 3

enum STRATEGY{
    UNREGISTERED, HORIZONTAL, VERTICAL, RANDOMWAYPOINT
};

enum STRATEGY string_to_strategy(char* str);

enum FISH_TYPE{
    INVALID, REDFISH,CLOWNFISH
};

enum FISH_TYPE string_to_fish_type(char* str);

struct fish{
    char* name;
    int running;
    enum FISH_TYPE type;
    enum STRATEGY strategy;
    struct position position;
    struct dimension rectangle;
};

/**
 * @fn              create_fish
 * @brief           create a fish using the given value for the parameters
 * @param fish_type the type of the fish to be created
 * @param strategy  the moving strategy of the fish to be created
 * @param x         the x coordinates of the fish
 * @param y         the y coordinates of the fish
 * @param width     the width of the fish
 * @param height    the height of the fish
 * @return          the adress of the strcuture fish created
 */
struct fish * create_fish(char * name,enum FISH_TYPE fish_type, enum STRATEGY strategy,int x,int y,int width,int height);

/**
 * @fn          free_fish
 *  @brief      liberate the memory allocated by the creation of the fish
 *  @param fish a pointer to a fish structure
 */
void free_fish(struct fish * fish);

/**
 * @brief    implement fish random move strategy
 * @param fish the string strategy to use for the fish get from the client
 */
void RandomWayPoint(struct fish *fish);

#endif
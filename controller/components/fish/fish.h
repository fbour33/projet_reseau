#ifndef AQUARIUM_FISH_H
#define AQUARIUM_FISH_H

#include "../../utilities/tools.h"

#define MAX_FISHES 7
#define MAX_WAYPOINT 5

enum STRATEGY{
    UNREGISTERED, HORIZONTAL, VERTICAL, RANDOMWAYPOINT
};

enum STRATEGY string_to_strategy(char* str);

struct waypoint{
    struct position pos;
    int total_time;
    int time_left;
};

struct waypoint *create_waypoint(int x, int y, int time);

//Aouter un temps de vie pour pouvoir calculer une position lorsque changement de vue
struct fish{
    char* name;
    int running;
    enum STRATEGY strategy;
    struct position position;
    struct dimension rectangle;
    int wps_nb;
    struct waypoint *waypoints[MAX_WAYPOINT];
};

/**
 * @fn              create_fish
 * @brief           create a fish using the given value for the parameters
 * @param strategy  the moving strategy of the fish to be created
 * @param x         the x coordinates of the fish
 * @param y         the y coordinates of the fish
 * @param width     the width of the fish
 * @param height    the height of the fish
 * @return          the adress of the strcuture fish created
 */
struct fish * create_fish(char * name, enum STRATEGY strategy,int x,int y,int width,int height);

/**
 * @fn          free_fish
 *  @brief      liberate the memory allocated by the creation of the fish
 *  @param fish a pointer to a fish structure
 */
void free_fish(struct fish * fish);

/**
 * @brief    add a Randomwaypoint to fish waypoints
 * @param fish the string strategy to use for the fish get from the client
 * @return  0 on success, -1 on failure
 */
int RandomWayPoint(struct fish *fish);

int run(struct fish* fish);

int end_waypoint(struct fish *fish);

#endif
#ifndef AQUARIUM_FISH_H
#define AQUARIUM_FISH_H
#include "../../utilities/fish_type.h"
#include "../../utilities/strategy.h"
#include "../../utilities/tools.h"


struct fish{
    enum FISH_TYPE type;
    enum STRATEGY strategy;
    struct position start_position;
    struct position final_position;
};

/**
 * @fn              create_fish
 * @brief           create a fish using the given value for the parameters
 * @param fish_type the type of the fish to be created
 * @param strategy  the moving strategy of the fish to be created
 * @param x_star    the x depature coordinates of the fish
 * @param y_start   the y depature coordinates of the fish
 * @param x_final   the x final coordinates of the fish
 * @param y_final   the y final coordinates of the fish
 * @return          the adress of the strcuture fish created
 */
struct fish * create_fish(enum FISH_TYPE fish_type,enum STRATEGY strategy,int x_start,int y_start,int x_final,int y_final);

/**
 * @fn          free_fish
 *  @brief      liberate the memory allocated by the creation of the fish
 *  @param fish a pointer to a fish structure
 */
void free_fish(struct fish * fish);
#endif
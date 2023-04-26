#ifndef AQUARIUM_TOOLS_H
#define AQUARIUM_TOOLS_H

#include <ctype.h>
#include <string.h>

/**
 * @brief check if an id is valid 
 * @return 1 on success 0 on failure
 */
int is_valid_ID(char* id);

/********** STRUCT POSITION *************/ 
struct position{
    int x;
    int y;
};

/**
 * @param x 
 * @param y 
 */
struct position _position(int x, int y);

/********** STRUCT DIMENSION *************/ 

struct dimension{
    int width;
    int height;
};

#endif
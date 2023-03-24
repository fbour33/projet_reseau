#ifndef AQUARIUM_TOOLS_H
#define AQUARIUM_TOOLS_H
#include "../components/view/view.h"

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
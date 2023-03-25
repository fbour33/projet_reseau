#ifndef AQUARIUM_VIEW_H
#define AQUARIUM_VIEW_H
#include "../../utilities/tools.h"
struct view{
    int id;
    struct dimension d;
    struct position p;
};

struct view * create_view(int id, int x, int y, int width, int height);
#endif
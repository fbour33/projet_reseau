#ifndef AQUARIUM_VIEW_H
#define AQUARIUM_VIEW_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../fish/fish.h"

struct view{
    int id;
    struct dimension d;
    struct position p;
    int free;   
    struct fish* fishes[MAX_FISHES];
    int nb_fishes; // 0->MAX_FISHES-1, first index NULL
};

int add_fish(struct view* view, struct fish* fish);

int delete_fish(struct view*, char*);

struct fish** get_fishes(struct view*);

int status(struct view*);

struct view * create_view(int id, int x, int y, int width, int height);

void free_view(struct view*);
#endif
#ifndef AQUARIUM_VIEW_H
#define AQUARIUM_VIEW_H

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

int get_fishes(struct view*, char *resp, int waypoint_idx);

int status(struct view*, char* resp);

struct view * create_view(int id, int x, int y, int width, int height);

void free_view(struct view*);

int fish_already_exists(struct fish* fish);

int start_fish(struct view*, char* name);

#endif
#ifndef AQUARIUM_H
#define AQUARIUM_H
#include"../view/view.h"
#include "../fish/fish.h"
#include "../../parser/parser.h"
#define MAX_VIEWS 15
#define MAX_FISHES 15
struct aquarium{
    struct dimension dimension;
    int num_aquarium_views;
    struct view *aquarium_views[MAX_VIEWS];
    struct fish *aquarium_fishes[MAX_FISHES];
};

/**
 * @fn      create_aquarium 
 * @brief   create a aquarium 
 * @return  the adress of the aquarium created
 */
struct aquarium *create_aquarium();


/**
 * @fn      load_aquarium
 * @brief   load a aquarium from the aquarium.load file  
 */

void load_aquarium(struct aquarium *aquarium);

/**
 * @fn  show_aquarium
 * @brief show the aquarium properties from the aquarium parameter
 * @param aquarium
 */

void show_aquarium(struct aquarium *aquarium);


/**
 * @fn      add_view_aquarium
 * @brief   add a new view to aquarium 
 * @param   aquarium 
 * @param   view
 */

void add_view_aquarium(struct aquarium* aquarium, struct view* view);

/**
 * @fn      del_view_aquarium
 * @brief   delete a view to the aquarium 
 * @param   aquarium 
 * @param   view
 */

void del_view_aquarium(struct aquarium* aquarium, int view_id);

/**
 * @fn      save_aquarium
 * @brief   export and save the current aquarium to the aquarium.load file
 * @param   aquarium 
 * @param   view
 */

void save_aquarium(struct aquarium* aquarium);

/**
 *  @fn             free_aquarium
 *  @brief          liberate the memory allocated by the creation of the aquarium
 *  @param aquarium a pointer to a aquarium
 */
void free_aquarium(struct aquarium * aquarium);
#endif
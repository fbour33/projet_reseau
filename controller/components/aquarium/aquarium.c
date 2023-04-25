#include "aquarium.h"

struct aquarium *global_aquarium;

/**
 * @fn      create aquarium 
 * @brief   create a aquarium 
 * @return  the adress of the aquarium created
 */
struct aquarium *create_aquarium(){
    struct aquarium *aquarium = malloc(sizeof(struct aquarium));
    aquarium->num_aquarium_views=0;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        aquarium->aquarium_views[i] = malloc(sizeof(struct view));
    }
    return aquarium;
}

/**
 * @fn      load_aquarium
 * @brief   load a aquarium from the aquarium.load file  
 */
void load_aquarium(struct aquarium *aquarium){
    parser_load_aquarium("../aquarium.load",aquarium);
    printf("\t-> aquarium loaded (%d display views) !\n",aquarium->num_aquarium_views);
}

/**
 * @fn  show_aquarium
 * @brief show the aquarium properties from the aquarium parameter
 * @param aquarium
 */
void show_aquarium(struct aquarium *aquarium){
    printf("%dx%d\n",aquarium->dimension.width,aquarium->dimension.height);
    for(int i=0;i<aquarium->num_aquarium_views;i++){
        printf("N%d %dx%d+%d+%d\n",aquarium->aquarium_views[i]->id, aquarium->aquarium_views[i]->p.x, aquarium->aquarium_views[i]->p.y, aquarium->aquarium_views[i]->d.width, aquarium->aquarium_views[i]->d.height);
    }
}

/**
 * @fn      add_view_aquarium
 * @brief   add a new view to the aquarium 
 * @param   aquarium 
 * @param   view
 */
void add_view_aquarium(struct aquarium* aquarium, struct view* view){
    aquarium->aquarium_views[aquarium->num_aquarium_views]=view;
    aquarium->num_aquarium_views++;
    printf("\t-> view added\n");
}

/**
 * @fn      del_view_aquarium
 * @brief   delete a view to the aquarium 
 * @param   aquarium 
 * @param   view
 */
void del_view_aquarium(struct aquarium* aquarium, int view_id){
    int status = 0;
    int index = 0;
    for(int i=0; i<aquarium->num_aquarium_views; i++){
        if(aquarium->aquarium_views[i]->id==view_id){
            // printf("id aquarium : %d, id :%d", aquarium->aquarium_views[i]->id, view_id);
            index=i;
            status++;
            break;
        }
    }

    if(status == 0) {
        printf("\t-> Your id doesn't exist\n");
        return ;
    }
    free(aquarium->aquarium_views[index]);
    for(int i=index;i<MAX_CLIENTS-1; i++){
        aquarium->aquarium_views[i]=aquarium->aquarium_views[i+1];
    }
    struct view *view = malloc(sizeof(struct view));
    aquarium->aquarium_views[MAX_CLIENTS-1]= view;
    aquarium->num_aquarium_views--;
    printf("\t-> view N%d deleted\n",view_id);
}

/**
 * @fn      save_aquarium
 * @brief   export and save the current aquarium to the aquarium.load file
 * @param   aquarium 
 * @param   view
 */

void save_aquarium(struct aquarium* aquarium){
    parser_save_aquarium("../aquarium.load",aquarium);
    printf("\t-> aquarium saved !(%d display views)\n",aquarium->num_aquarium_views);
}

/**
 *  @fn             free_aquarium
 *  @brief          liberate the memory allocated by the creation of the aquarium
 *  @param aquarium a pointer to a aquarium
 */
void free_aquarium(struct aquarium * aquarium){
    // free view array
    for(int i=0; i<MAX_CLIENTS;i++){
        free(aquarium->aquarium_views[i]);
    }

    // free aquarium
    free(aquarium);
}

/** 
 * @fn             parser_load_aquarium
 * @brief          enable to get data from aquarium.load file to initialize the aquarium
 * @param file     the path to the aquarium.load
 * @param aquarium     the adress of the aquarium
**/

void parser_load_aquarium(char *file,struct aquarium *aquarium){
    FILE *aquarium_load_file;
    char line[MAX_LENGTH];
    int i =1;
    aquarium_load_file = fopen(file,"r");
    if(aquarium_load_file==NULL){
        printf("Couldn't open aquarium load file");
        return; 
    }
    while(fgets(line,MAX_LENGTH,aquarium_load_file)!=NULL){
        if(strlen(line) > 1){
            if(i==1){
                if (sscanf(line, "%dx%d", &aquarium->dimension.width, &aquarium->dimension.height) != 2) {
                    printf("Error reading aquarium size\n");
                    return;
                }
            }else if(i>1){
                if(sscanf(line, "N%d %dx%d+%d+%d", &aquarium->aquarium_views[aquarium->num_aquarium_views]->id, &aquarium->aquarium_views[aquarium->num_aquarium_views]->p.x, &aquarium->aquarium_views[aquarium->num_aquarium_views]->p.y, &aquarium->aquarium_views[aquarium->num_aquarium_views]->d.width, &aquarium->aquarium_views[aquarium->num_aquarium_views]->d.height)!=5){
                    printf("Error reading line: %s", line);
                    return;
                }
                aquarium->aquarium_views[aquarium->num_aquarium_views]->free = 1;
                aquarium->num_aquarium_views++;
            }
        i++;
        } 
    }
    fclose(aquarium_load_file);
}

/** 
 * @fn             parser_save_aquarium
 * @brief          write data to aquarium.load file
 * @param file     the path to the aquarium.load
 * @param aquarium the adress of the aquarium
**/
void parser_save_aquarium(char *file,struct aquarium *aquarium){
    FILE *aquarium_load_file;
    aquarium_load_file = fopen(file,"w");
    if(aquarium_load_file==NULL){
        printf("Couldn't open aquarium load file");
        return; 
    }
    fprintf(aquarium_load_file,"%dx%d\n",aquarium->dimension.width,aquarium->dimension.height);
    for(int i=0;i<aquarium->num_aquarium_views;i++){
        fprintf(aquarium_load_file,"N%d %dx%d+%d+%d\n",aquarium->aquarium_views[i]->id,aquarium->aquarium_views[i]->p.x,aquarium->aquarium_views[i]->p.y,aquarium->aquarium_views[i]->d.width,aquarium->aquarium_views[i]->d.height);
    }
    fclose(aquarium_load_file);
}

int get_idx_from_id(int id){
    for(int i=0; i<MAX_CLIENTS;i++){
        if(id == global_aquarium->aquarium_views[i]->id){
            return i;
        }
    }
    return -1;
}
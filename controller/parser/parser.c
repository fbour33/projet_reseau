#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

/** 
 * @fn             parser_controller_config_file
 * @brief          enable to get data from controller config file to initialize the server
 * @param file     the path to the controller config file
 * @param port     the adress of the variable containing the port value
 * @param timeout  the adress of the variable containing the display-timeout value
 * @param interval the adress of the variable containing the fish-update-interval value
**/
void parser_controller_config_file(const char *file, int *port, int *timeout, int *interval){
    FILE *config_file;
    char line[MAX_LENGTH];

    config_file = fopen(file,"r");
    if(config_file==NULL){
        printf("Couldn't open config file");
        return; 
    }
    
    while(fgets(line,MAX_LENGTH,config_file)!=NULL){
        if(strlen(line) > 1){
            char* variable = strtok(line, "=");
            char* value = strtok(NULL, "=");
            if (variable != NULL && value != NULL) {
                if (strcmp(variable, "controller-port") == 0) {
                    *port = atoi(value);
                }
                else if (strcmp(variable, "display-timeout-value") == 0) {
                    *timeout = atoi(value);
                }
                else if (strcmp(variable, "fish-update-interval") == 0) {
                    *interval = atoi(value);
                }
            }
        }
    }
    fclose(config_file);
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
        fprintf(aquarium_load_file,"N%i %dx%d+%d+%d\n",aquarium->aquarium_views[i]->id,aquarium->aquarium_views[i]->p.x,aquarium->aquarium_views[i]->p.y,aquarium->aquarium_views[i]->d.width,aquarium->aquarium_views[i]->d.height);
    }
    fclose(aquarium_load_file);
}


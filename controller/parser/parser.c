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
    int max_length=64;
    FILE *config_file;
    char line[max_length];

    config_file = fopen(file,"r");
    if(config_file==NULL){
        printf("Couldn't open config file");
        return; 
    }
    
    while(fgets(line, max_length, config_file)!=NULL){
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








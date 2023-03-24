#ifndef AQUARIUM_PARSER
#define AQUARIUM_PARSER
#include "../components/aquarium/aquarium.h"
#define MAX_LENGTH 25

/** 
 * @fn             parser_controller_config_file
 * @brief          enable to get data from controller config file to initialize the server
 * @param file     the path to the controller config file
 * @param port     the adress of the variable containing the port value
 * @param timeout  the adress of the variable containing the display-timeout value
 * @param interval the adress of the variable containing the fish-update-interval value
**/
void parser_controller_config_file(const char *file, int *port, int *timeout, int *interval);

/** 
 * @fn             parser_load_aquarium
 * @brief          enable to get data from aquarium.load file to initialize the aquarium
 * @param file     the path to the aquarium.load
 * @param aquarium the adress of the aquarium
**/
void parser_load_aquarium(char *file,struct aquarium *aquarium);

/** 
 * @fn             parser_save_aquarium
 * @brief          write data to aquarium.load file
 * @param file     the path to the aquarium.load
 * @param aquarium the adress of the aquarium
**/
void parser_save_aquarium(char *file,struct aquarium *aquarium);
#endif
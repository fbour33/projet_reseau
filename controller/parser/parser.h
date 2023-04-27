#ifndef AQUARIUM_PARSER
#define AQUARIUM_PARSER

/** 
 * @fn             parser_controller_config_file
 * @brief          enable to get data from controller config file to initialize the server
 * @param file     the path to the controller config file
 * @param port     the adress of the variable containing the port value
 * @param timeout  the adress of the variable containing the display-timeout value
 * @param interval the adress of the variable containing the fish-update-interval value
**/
void parser_controller_config_file(const char *file, int *port, int *timeout, int *interval);

#endif
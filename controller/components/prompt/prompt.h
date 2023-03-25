#ifndef AQUARIUM_PROMPT_H
#define AQUARIUM_PROMPT_H
#define GREENBOLD "\e[32;1m"

enum COMMAND{
    LOAD, SHOW, ADD, DEL, SAVE
};

/**
 * @brief main function of the prompt
 * @note it is the function which will be given to the thread
 */
void * main_prompt_menu(void *args);

/**
 * @brief function for handling the prompt entry
 * @return 1 on success, 0 on failure
 */
int handle_command_line(char *command_line);

/**
 * @brief function for calling the right callback function
 * @return 1 on success, 0 on failure
 */
int call_command(enum COMMAND command);

/**
 * @brief function called when a load command is received
 * @return 1 on success, 0 on failure
 */
int command_load_aquarium();

/**
 * @brief function called when the show command is received
 * @return 1 on success, 0 on failure
 */
int command_show_aquarium();

/**
 * @brief function called when the add command is received
 * @return 1 on success, 0 on failure
 */
int command_add_aquarium();

/**
 * @brief function called when the delete command is received
 * @return 1 on success, 0 on failure
 */
int command_del_aquarium();

/**
 * @brief function called when the save command is received
 * @return 1 on success, 0 on failure
 */
int command_save_aquarium();
#endif
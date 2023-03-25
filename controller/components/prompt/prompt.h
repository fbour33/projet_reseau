#ifndef AQUARIUM_PROMPT_H
#define AQUARIUM_PROMPT_H
#define GREENBOLD "\e[32;1m"

enum COMMAND{
    LOAD, SHOW, ADD, DEL, SAVE
};
void * main_prompt_menu(void *args);
int handle_command_line(char *command_line);
int call_command(enum COMMAND command);
int command_load_aquarium();
int command_show_aquarium();
int command_add_aquarium();
int command_del_aquarium();
int command_save_aquarium();
#endif
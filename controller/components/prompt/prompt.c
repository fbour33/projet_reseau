#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prompt.h"
#include "../../global.h"
#define MAX_COMMAND_LENGTH 32

/**
 * @brief function for handling the prompt entry
 * @return 0 on success, -1 on failure, 1 for exit
 */
int handle_command_line(char *command_line){
    char *token;
    char *delim = " ";
    if (strncmp(command_line, "quit",4)==0 || strncmp(command_line, "exit",4)==0){
        printf("\t-> bye\n");
        return 1;
    }
    token = strtok(command_line, delim);

    if(strncmp(token, "load",4) == 0){
        return call_command(LOAD);
    }
    else if(strncmp(token, "show",4) == 0){
        return call_command(SHOW);
    }
    else if(strncmp(token, "add",3) == 0){
        return call_command(ADD);
    }
    else if(strncmp(token, "del",3) == 0){
        return call_command(DEL);
    }
    else if(strncmp(token, "save\n",4) == 0){
        return call_command(SAVE);
    }
    else{
        printf("\t-> Invalid command\n");
        return 0;
    }
    return -1;
}

/**
 * @brief function for calling the right callback function
 * @return 0 on success, -1 on failure
 */
int call_command(enum COMMAND command){
    if(global_aquarium==NULL && command!=LOAD){
        printf("\t-> Impossible to execute a command on non-existing aquarium\n");
        return -1;
    }
    
    switch (command){
    case LOAD:
        return command_load_aquarium();
    case SHOW:
        return command_show_aquarium();
    case ADD:
        return command_add_aquarium();
    case DEL:
        return command_del_aquarium();
    case SAVE:
        return command_save_aquarium();
    default:
        break;
    }

    return -1;
}

/**
 * @brief function called when a load command is received
 * @return 0 on success, -1 on failure
 */
int command_load_aquarium(){
    char *delim = " ";
    char *string = strtok(NULL, delim);
    if(string==NULL){
        printf("\t-> you need to load something\n");
        return 0;
    }
    if(strncmp(string,"aquarium", 8)!=0){
        printf("\t-> invalid string after load command\n");
        return 0;
    }
    global_aquarium = create_aquarium();
    load_aquarium(global_aquarium);
    return 0;
    
}

/**
 * @brief function called when the show command is received
 * @return 0 on success, -1 on failure
 */
int command_show_aquarium(){
    show_aquarium(global_aquarium);
    return 0;
}

/**
 * @brief function called when the add command is received
 * @return 0 on success, -1 on failure
 */
int command_add_aquarium(){
    char *delim = " ";
    char *string = strtok(NULL, delim);
    if(string==NULL){
        printf("\t-> you need to add something\n");
        return -1;
    }
    if (strncmp(string, "view", 4) != 0) {
        printf("\t-> you have to add a view\n");
        return -1;
    }
    char *id = strtok(NULL, delim);
    if(id==NULL){
        printf("\t-> invalid command\n");
        return -1;
    }
    char *x,*y,*width,*height;
    int num = atoi(id+1);
    x = strtok(NULL, delim);
    y = strtok(NULL, delim);
    width = strtok(NULL, delim);
    height = strtok(NULL, delim);
    struct view *view = malloc(sizeof(struct view));
    view->id=num;
    view->d.height=atoi(height);
    view->d.width=atoi(width);
    view->p.x=atoi(x);
    view->p.y=atoi(y);
    add_view_aquarium(global_aquarium,view);
    return 0;
}

/**
 * @brief function called when the delete command is received
 * @return 0 on success, -1 on failure
 */
int command_del_aquarium(){
    char *delim = " ";
    char *string = strtok(NULL, delim);
    if(string==NULL){
        printf("\t-> you need to delete something\n");
        return -1;
    }
    if (strncmp(string, "view", 4) != 0) {
        printf("\t-> you have to delete a view\n");
        return -1;
    }
    char *id = strtok(NULL, delim);
    if(id==NULL){
        printf("\t-> invalid command\n");
        return -1;
    }
    int num = atoi(id+1);
    del_view_aquarium(global_aquarium,num);

    return 0;
}

/**
 * @brief function called when the save command is received
 * @return 0 on success, -1 on failure
 */
int command_save_aquarium(){
    save_aquarium(global_aquarium);
    return 0;
}
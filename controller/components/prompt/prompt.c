#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prompt.h"
#include "../../utilities/mutex.h"
#include "../../global.h"
#define MAX_COMMAND_LENGTH 32

/**
 * @brief main function of the prompt
 * @note it is the function which will be given to the thread
 */
void * main_prompt_menu(void *args){
    char command[MAX_COMMAND_LENGTH];
    while (1) {
        printf(GREENBOLD"aquarium: $ ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
        if (!handle_command_line(command)) {
            break;
        }
    }
}

/**
 * @brief function for handling the prompt entry
 * @return 1 on success, 0 on failure
 */
int handle_command_line(char *command_line){
    char *token;
    char *delim = " ";
    if (strncmp(command_line, "quit",4)==0 || strncmp(command_line, "exit",4)==0){
        printf("\t->bye\n");
        return 0;
    }
    token = strtok(command_line, delim);
    if (token == NULL){
        return 0;
    }else{
        if(strncmp(token, "load",4) == 0){
            call_command(LOAD);
        }
        else if(strncmp(token, "show",4) == 0){
            call_command(SHOW);
        }
        else if(strncmp(token, "add",3) == 0){
            call_command(ADD);
        }
        else if(strncmp(token, "del",3) == 0){
            call_command(DEL);
        }
        else if(strncmp(token, "save\n",4) == 0){
            call_command(SAVE);
        }
        else{
            printf("\t-> Invalid command\n");
        }
    }
    return 1;
}

/**
 * @brief function for calling the right callback function
 * @return 1 on success, 0 on failure
 */
int call_command(enum COMMAND command){
    if(global_aquarium==NULL && command!=LOAD){
        printf("\t-> Impossible to execute a command on non-existing aquarium\n");
    }
    else{
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
    }
}

/**
 * @brief function called when a load command is received
 * @return 1 on success, 0 on failure
 */
int command_load_aquarium(){
    char *delim = " ";
    char *string = strtok(NULL, delim);
    if(string==NULL){
        printf("\t-> you need to load something\n");
        return 0;
    }
    if(strcmp(string,"aquarium")!=0){
        printf("\t-> invalid string after load command\n");
        return 0;
    }
    pthread_mutex_lock(&mutex_aquarium);
    global_aquarium = create_aquarium();
    load_aquarium(global_aquarium);
    pthread_mutex_unlock(&mutex_aquarium);
}

/**
 * @brief function called when the show command is received
 * @return 1 on success, 0 on failure
 */
int command_show_aquarium(){
    show_aquarium(global_aquarium);
}

/**
 * @brief function called when the add command is received
 * @return 1 on success, 0 on failure
 */
int command_add_aquarium(){
    char *delim = " ";
    char *string = strtok(NULL, delim);
    printf("%s\n", string);
    if(string==NULL){
        printf("\t-> you need to add something\n");
        return 0;
    }
    else{

        char *id,*x,*y,*width,*height;
        id = strtok(NULL, " ");
        if(id==NULL){
            printf("\t->Invalid command\n");
            return 0;
        }
        int num = atoi(id+1);
        x = strtok(NULL, "x");
        y = strtok(NULL, "+");
        width = strtok(NULL, "+");
        height = strtok(NULL, "+");
        struct view *view = malloc(sizeof(struct view));
        view->id=num;
        view->d.height=atoi(height);
        view->d.width=atoi(width);
        view->p.x=atoi(x);
        view->p.y=atoi(y);
        pthread_mutex_lock(&mutex_aquarium);
        add_view_aquarium(global_aquarium,view);
        pthread_mutex_unlock(&mutex_aquarium);
    }
    
}

/**
 * @brief function called when the delete command is received
 * @return 1 on success, 0 on failure
 */
int command_del_aquarium(){
    char *delim = " ";
    char *string = strtok(NULL, delim);
    char *id;
    id = strtok(NULL, " ");
    int num = atoi(id+1);
    pthread_mutex_lock(&mutex_aquarium);
    del_view_aquarium(global_aquarium,num);
    pthread_mutex_unlock(&mutex_aquarium);
}

/**
 * @brief function called when the save command is received
 * @return 1 on success, 0 on failure
 */
int command_save_aquarium(){
    save_aquarium(global_aquarium);
}

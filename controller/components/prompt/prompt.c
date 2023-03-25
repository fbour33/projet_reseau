#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "prompt.h"
#include "../../global.h"
#define MAX_COMMAND_LENGTH 32



void * main_prompt_menu(void *args){
    char command[MAX_COMMAND_LENGTH];
    while (1) {
        printf(GREENBOLD"aquarium$ ");
        fgets(command, MAX_COMMAND_LENGTH, stdin);
        if (!handle_command_line(command)) {
            break;
        }
    }
}

int handle_command_line(char *command_line){
    char *token;
    char *delim = " ";
    token = strtok(command_line, delim);

    if (token == NULL){
        return 0;
    }else{
        if(strcmp(token, "load")==0){
            call_command(LOAD);
        }
        else if(strcmp(token, "show")==0){
            call_command(SHOW);
        }
        else if(strcmp(token, "add")==0){
            call_command(ADD);
        }
        else if(strcmp(token, "del")==0){
            call_command(DEL);
        }
        else if(strcmp(token, "save")==0){
            call_command(SAVE);
        }
        else{
            printf("\t-> Invalid command\n");
        }
    }
    return 1;
}

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

int command_load_aquarium(){
    global_aquarium = create_aquarium(); // pour le moment j'initialise l'aquarium ici
    load_aquarium(global_aquarium);
}
int command_show_aquarium(){
    show_aquarium(global_aquarium);
}

int command_add_aquarium(){
    char *delim = " ";
    char *string = strtok(NULL, delim);
    if(string==NULL){
        printf("\t-> invalid string after add command\n");
        return 0;
    }
    else{

        char *id,*x,*y,*width,*height;
        id = strtok(NULL, " ");
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
        add_view_aquarium(global_aquarium,view);
    }
    
}

int command_del_aquarium(){
    char *delim = " ";
    char *string = strtok(NULL, delim);
    char *id;
    id = strtok(NULL, " ");
    int num = atoi(id+1);
    del_view_aquarium(global_aquarium,num);
}

int command_save_aquarium(){
    save_aquarium(global_aquarium);
}

#include "prompt.h"

int is_new_id(char* id) {
    for(int i = 0; i < global_aquarium->num_aquarium_views; ++i) {
        if(global_aquarium->aquarium_views[i]->id == atoi(id+1)) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief function for handling the prompt entry
 * @return 0 on success, -1 on failure, 1 for exit
 */
int handle_command_line(char *command_line){
    char *token;
    char *delim = " ";
    if (strncmp(command_line, "quit",4)==0 || strncmp(command_line, "exit",4)==0){
        fprintf(log_f, "\t-> bye\n");
        return EXIT_VALUE;
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
        fprintf(log_f, "\t-> Invalid command\n");
        return SUCCESS;
    }
    return ERROR;
}

/**
 * @brief function for calling the right callback function
 * @return 0 on success, -1 on failure
 */
int call_command(enum COMMAND command){
    if(global_aquarium==NULL && command!=LOAD){
        fprintf(log_f, "\t-> Impossible to execute a command on non-existing aquarium\n");
        return ERROR;
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

    return ERROR;
}

/**
 * @brief function called when a load command is received
 * @return 0 on success, -1 on failure
 */
int command_load_aquarium(){
    char *delim = " ";
    char *string = strtok(NULL, delim);
    if(string==NULL){
        fprintf(log_f, "\t-> you need to load something\n");
        return ERROR;
    }
    if(strncmp(string,"aquarium", 8)!=0){
        fprintf(log_f, "\t-> invalid string after load command\n");
        return ERROR;
    }
    global_aquarium = create_aquarium();
    load_aquarium(global_aquarium);
    return SUCCESS;
    
}

/**
 * @brief function called when the show command is received
 * @return 0 on success, -1 on failure
 */
int command_show_aquarium(){
    show_aquarium(global_aquarium);
    return SUCCESS;
}

/**
 * @brief function called when the add command is received
 * @return 0 on success, -1 on failure
 */
int command_add_aquarium(){
    char *delim = " ";
    char *string = strtok(NULL, delim);
    if(string==NULL){
        fprintf(log_f, "\t-> you need to add a view\n");
        return ERROR;
    }
    if (strncmp(string, "view", 4) != 0) {
        fprintf(log_f, "\t-> you need to add a view\n");
        return ERROR;
    }

    char *id = strtok(NULL, delim);
    if(id==NULL || !is_valid_id(id)){
        fprintf(log_f, "\t-> invalid id\n");
        return ERROR;
    }

    if(!is_new_id(id)) {
        fprintf(log_f, "\t-> this id already exist\n");
        return ERROR;
    }

    if(global_aquarium->num_aquarium_views >= MAX_CLIENTS) {
        fprintf(log_f, "\t-> View count limit reached\n");
        return ERROR;
    }

    char *x,*y,*width,*height;
    int num = atoi(id+1);
    x = strtok(NULL, delim);
    y = strtok(NULL, delim);
    width = strtok(NULL, delim);
    height = strtok(NULL, delim);

    if(x ==NULL || y == NULL || width ==NULL || height == NULL) {
        fprintf(log_f, "\t-> 4 parameters needed\n");
        return ERROR;
    }
    if(is_number(x) && is_number(y) && is_number(width) && is_number(height) == 0) {
        fprintf(log_f, "\t-> your paramters must be integer\n");
        return ERROR;
    }
    if(atoi(x) < 0 || atoi(x) > 100) {
        fprintf(log_f, "\t-> x must be between 0 and 100\n");
        return ERROR;
    }
    if(atoi(y) < 0 || atoi(y) > 100) {
        fprintf(log_f, "\t-> y must be between 0 and 100\n");
        return ERROR;
    }

    struct view *view = create_view(num, atoi(x), atoi(y), atoi(width), atoi(height));
    add_view_aquarium(global_aquarium,view);
    return SUCCESS;
}

/**
 * @brief function called when the delete command is received
 * @return 0 on success, -1 on failure
 */
int command_del_aquarium(){
    char *delim = " ";
    char *string = strtok(NULL, delim);
    if(string==NULL){
        fprintf(log_f, "\t-> you need to delete something\n");
        return ERROR;
    }
    if (strncmp(string, "view", 4) != 0) {
        fprintf(log_f, "\t-> you have to delete a view\n");
        return ERROR;
    }
    char *id = strtok(NULL, delim);
    if(id==NULL){
        fprintf(log_f, "\t-> invalid id\n");
        return ERROR;
    }
    if(global_aquarium->num_aquarium_views == 0) {
        fprintf(log_f, "\t-> There is no more view\n");
        return ERROR;
    }
    int num = atoi(id+1);
    del_view_aquarium(global_aquarium,num);

    return SUCCESS;
}

/**
 * @brief function called when the save command is received
 * @return 0 on success, -1 on failure
 */
int command_save_aquarium(){
    save_aquarium(global_aquarium);
    return SUCCESS;
}
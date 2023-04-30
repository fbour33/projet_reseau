#include "tools.h"

int controller_port;
int display_timeout;
int fish_update_interval;

unsigned long t = 0;

FILE* log_f;

/******* STRUCT POSITION*******/

struct position _position(int x, int y){
    struct position p = { x, y };
    return p;
}

/**
 * @brief check if an id is valid 
 * @return 1 on success 0 on failure
 */
int is_valid_ID(char* id){
	if(strlen(id) < 2){
		return 0;
	}
	if(id[0] == 'N') {
		for(int i =1; i< strlen(id)-1; i++){
			if(!isdigit(id[i])){
				return 0;
			}
		}
		if(id[strlen(id)-1] == '\n'){
			return 1;
		}
	}
	return 0;
}

int is_valid_id(char* id){
	if(strlen(id) < 2){
		return 0;
	}
	if(id[0] == 'N') {
		for(int i =1; i< strlen(id)-1; i++){
			if(!isdigit(id[i])){
				return 0;
			}
		}
	}
	return 1;
}

/**
 * @brief check if an string is a number 
 * @return 1 on success 0 on failure
 */
int is_number(char* number) {
	if(number == NULL) {
		return 0;
	}
	for(int i = 0; i < strlen(number)-1; i++) {
		if(!isdigit(number[i])) {
			return 0;
		}
	}
	return 1;
}

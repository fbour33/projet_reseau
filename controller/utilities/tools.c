#include "tools.h"

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
	}
	return 1;
}

int is_valid_number(char* number) {
	for(int i = 0; i < strlen(number)-1; i++) {
		if(!isdigit(number[i])) {
			return 0;
		}
	}
	return 1;
}

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
	if(strlen(id) <= 2){
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

/**
 * @brief check if an string is a number 
 * @return 1 on success 0 on failure
 */
int is_number(char* txt){
	if(txt == NULL){
		return -1;
	}
    for(int i=0; i<strlen(txt); i++){
		if(!isdigit(txt[i])){
			return 0;
		}
	}
	return 1;
}

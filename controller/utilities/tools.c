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

/******* STRUCT DIMENSION *******/

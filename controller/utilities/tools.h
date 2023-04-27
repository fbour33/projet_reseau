#ifndef AQUARIUM_TOOLS_H
#define AQUARIUM_TOOLS_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>


/********** STRUCT POSITION *************/ 
struct position{
    int x;
    int y;
};

/**
 * @param x 
 * @param y 
 */
struct position _position(int x, int y);

/********** STRUCT DIMENSION *************/ 

struct dimension{
    int width;
    int height;
};

/**
 * @brief check if an id is valid 
 * @return 1 on success 0 on failure
 */
int is_valid_ID(char* id);

int is_valid_id(char* id);

/**
 * @brief check if an string is a number 
 * @return 1 on success 0 on failure
 */
int is_number(char* number);

#endif
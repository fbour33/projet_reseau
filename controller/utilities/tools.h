#ifndef AQUARIUM_TOOLS_H
#define AQUARIUM_TOOLS_H

#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctype.h>
#include <stddef.h>

/**
 * @brief check if an id is valid 
 * @return 1 on success 0 on failure
 */
int is_valid_ID(char* id);

/**
 * @brief check if a number is valid 
 * @return 1 on success 0 on failure
 */
int is_valid_number(char* number);

/**
 * @brief check if an id is new (view)
 * @return 1 on success 0 on failure
 */
int is_new_id(char* id);

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

#endif
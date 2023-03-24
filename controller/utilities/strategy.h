#ifndef AQUARIUM_FISH_STRATEGY
#define AQUARIUM_FISH_STRATEGY


enum STRATEGY{
    HORIZONTAL, VERTICAL, RANDOM, UNREGISTERED
};

/**
 * convert a string value of a strategy get from the client to a enum value 
 * @param strategy the string strategy to use for the fish get from the client
 */
enum STRATEGY get_strategy_from_string(char *strategy);
#endif
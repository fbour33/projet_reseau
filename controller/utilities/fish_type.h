#ifndef AQUARIUM_FISH_TYPE
#define AQUARIUM_FISH_TYPE

enum FISH_TYPE{
    REDFISH,CLOWNFISH
};

/**
 * convert a string value of a fish type get from the client to a enum value 
 * @param fish_type the string fish type to use for the fish get from the client
 */
enum  FISH_TYPE get_fish_type_from_string(char *fish_type);
#endif
/**
* @file
* @brief Useful global defines
*/

#pragma once
#include <stdbool.h>

#define NUM_DIRECTIONS 3

/**
* @brief Direction enum with up, down and none
*/
typedef enum
{
    UP = 0,
    DOWN = 1,
    NONE = 2
} Direction;

/**
* @brief Retrieves the elevator's number of floors.
*
* @return the number of floors.
*/
int numFloors();
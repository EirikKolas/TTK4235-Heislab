/**
* @file
* @brief Useful global defines
*/

#pragma once
#include <stdbool.h>

#define NUM_DIRECTIONS 3

/**
* @brief Direction enum with the directions @p UP, @p DOWN and @p NONE .
*/
typedef enum
{
    UP = 0,     /* Direction up */
    DOWN = 1,   /* Direction down */
    NONE = 2    /* No direction */
} Direction;

/**
* @brief Retrieves the elevator's number of floors.
*
* @return the number of floors.
*/
int numFloors();
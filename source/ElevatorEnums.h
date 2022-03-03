/**
* @file
* @brief Useful global defines
*/

#pragma once
#include <stdbool.h>

#define NUM_DIRECTIONS 3

typedef enum
{
    UP = 0,
    DOWN = 1,
    NONE = 2
} Direction;

int numFloors();
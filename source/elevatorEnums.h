#pragma once
#include <stdbool.h>

/*
typedef enum
{
    MOVING = 0,
    STOP_FLOOR = 1,
    STOP_BETWEEN = 2
} Action;
*/
#define NUM_DIRECTIONS 3

typedef enum
{
    UP = 0,
    DOWN = 1,
    NONE = 2
} Direction;

int numFloors();
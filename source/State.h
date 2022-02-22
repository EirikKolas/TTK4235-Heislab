#pragma once
typedef enum
{
    MOVING = 0,
    STOP_FLOOR = 1,
    STOP_BETWEEN = 2
} Action;

typedef enum
{
    DOWN = 0,
    UP = 1,
    STOP = 2
} Direction;

int getLastFloor();
Action getAction();
Direction getDirection();

void updateLastFloor();
void setDirection(Direction dir);
void setAction(Action a);

void initOrtState();
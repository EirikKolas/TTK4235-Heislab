#pragma once
#include "elevatorEnums.h"

int getLastFloor();
Action getAction();
Direction getDirection();

void updateLastFloor();
void setDirection(Direction dir);
void setAction(Action a);

void initOrtState();
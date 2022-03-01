#pragma once
#include "elevatorEnums.h"

int getLastFloor();
int getFloor();

Direction getDirection();

void updateLastFloor();
void setDirection(Direction dir);

void initOrtState();
void swapDirection();

/**
* @file
* @brief Logic for storing the direction and the location of the elevator
*/

#pragma once
#include "ElevatorEnums.h"

int getLastFloor();
int getFloor();

Direction getDirection();

void updateLastFloor();
void setDirection(Direction dir);

void swapDirection();

/**
* @file
* @brief Module for updating elevator lights
*/

#pragma once
#include "ElevatorEnums.h"

void initLights();
void clearButtonLamps(int floor);
void setButtonLamp(int floor, Direction dir);
void clearAllButtonLamps();
void setFloorIndicator(int floor);

void setDoorLight();
void clearDoorLight();

void setStopLamp();
void clearStopLamp();

#pragma once
#include "elevatorEnums.h"

void initLights();
void clearButtonLamps(int floor);
void setButtonLamp(int floor, Direction dir);
void clearAllButtonLamps();
void setFloorIndicator(int floor);

void setDoorLight();
void clearDoorLight();

void setStopLamp();
void clearStopLamp();

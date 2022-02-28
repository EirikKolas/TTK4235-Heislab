#pragma once
#include "elevatorEnums.h"

void initLights();
void activateButtonLamps();
void deactivateButtonLamps(int floor);
void setButtonlamp(int floor, Direction dir, bool value);

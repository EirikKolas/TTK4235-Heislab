/**
* @file
* @brief Simple interface for operating the elevator motor
*/

#pragma once
#include "State.h"

void initMotor();
void findFloor();
void move(Direction dir);
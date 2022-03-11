/**
* @file
* @brief Simple interface for operating the elevator motor
*/

#pragma once
#include "State.h"

/**
* @brief Initializes the motor.
*/
void initMotor();

/**
* @brief Turns off the motor or turns on the motor in a specific direction.
*
* @param[in] dir Direction of the motor. The direction can be @c NONE, which will stop the elevator.
*/
void move(Direction dir);
/**
* @file
* @brief Simple interface for checking elevator buttons
*/

#pragma once
#include "ElevatorEnums.h"

/**
* @brief Checks if a specific button is pressed
*
* @param[in] floor Elevator floor where the button is located.
* @param[in] dir Type of button to be checked.
*
* @return false if button not pressed, true if button pressed
*/
bool isButtonPressed(int floor, Direction dir);


/**
* @brief Checks if there is an obstruction
*
* @return true if there is an obstruction, false otherwise
*/
bool isObstructed();


/**
* @brief Checks if the stop button is pressed
*
* @return true if the stop button is pressed, false otherwise
*/
bool isStopPressed();


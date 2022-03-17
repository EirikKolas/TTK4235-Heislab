/**
* @file
* @brief Module for updating elevator lights
*/

#pragma once
#include "ElevatorEnums.h"


/**
* @brief Makes sure all the lights are off when the elevator initializes.
*/
void initLights();

/**
* @brief Clears all the button lamps at a specific floor.
*
* @param[in] floor Elevator floor where the buttons are located.
*/
void clearButtonLamps(int floor);

/**
* @brief Turs the light on, on a specific button at a specific floor.
*
* @param[in] floor Elevator floor where the button is located.
* @param[in] dir Type of button to be turned on.
*/
void setButtonLamp(int floor, Direction dir);


/**
* @brief Turns off all the button lamps at all floors.
*/
void clearAllButtonLamps();

/**
* @brief Turns on the floor indicator lamp at the floor where the elevator is.
*
* @param[in] floor Elevator floor where the lamp is to be turned on.
*/
void setFloorIndicator(int floor);

/**
* @brief Turns on the door lamp.
*/
void setDoorLight();

/**
* @brief Turns off the door lamp.
*/
void clearDoorLight();

/**
* @brief Turns on the stop lamp.
*/
void setStopLamp();

/**
* @brief Turns off the stop lamp.
*/
void clearStopLamp();

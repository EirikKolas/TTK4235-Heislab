/**
* @file
* @brief Logic for storing the direction and the location of the elevator.
*/

#pragma once
#include "ElevatorEnums.h"

/**
 * @brief Gets the floor which the elevator most recently passed or stopped at.
 * 
 * @return the floor which the elevator most recently passed or stopped at.
 */
int getLastFloor();

/**
 * @brief Gets the position of the elevator.
 * 
 * @return the floor where the elevator is or -1 if it is between floors.
 */
int getFloor();

/**
 * @brief Gets the directions of the elevator.
 * 
 * @return the direction the elevator is moving.
 */
Direction getDirection();

/**
 * @brief Updates which floor should be considered the last floor.
 */
void updateLastFloor();

/**
 * @brief Sets the direction of the elevator to @p dir .
 * 
 * @param[in] dir The direction of which the elevator is to be set.
 */
void setDirection(Direction dir);

/**
 * @brief Swaps the direction of the elevator from up to down and vice versa.
 */
void swapDirection();

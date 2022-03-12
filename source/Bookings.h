/**
* @file
* @brief Module for handling elevator bookings.
*/

#pragma once
#include "ElevatorEnums.h"

#define NO_BOOKINGS -1

/**
* @brief Makes sure there aren't any active bookings when the elevator is initialiazed.
*/
void initBookings();

/**
* @brief Clears all bookings at a specific @p floor .
*
* @param[in] floor Elevator floor where the bookings are to be cleared.
*/
void clearBooking(int floor);

/**
* @brief Checks all bookings at all floors.
*/
void clearAllBookings();

/**
* @brief Sets an active booking with a direction @p dir on a specific @p floor .
*
* @param[in] floor Elevator floor where the booking is set.
* @param[in] dir Direction of the booking.
*/
void setBooking(int floor, Direction dir);

/**
* @brief Calculates the next destination from all the active bookings based on the elevator's @p lastFloor and direction @p dir .
*
* @param[in] lastFloor Floor where the elevator is located.
* @param[in] dir Direction of the elevator.
*
* @return the next floor.
*/
int  getNextDestination(int lastFloor, Direction dir);
/**
* @file
* @brief Module for handling elevator bookings
*/

#pragma once
#include "ElevatorEnums.h"

#define NO_BOOKINGS -1

void initBookings();
void clearBooking(int floor);
void clearAllBookings();
void setBooking(int floor, Direction dir);
int  getNextDestination(int currentFloor, Direction dir);
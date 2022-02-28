#pragma once
#include "elevatorEnums.h"

void initBookings();
void clearLevel();
void clearAllLevels();
void checkBookings();
void setBooking(int floor, Direction dir);
int getNextDestination(int currentFloor, Direction dir);
void swapDirection();
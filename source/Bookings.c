#include "Bookings.h"
#include "ElevatorEnums.h"
#include <stdbool.h>
#include "driver/elevio.h"
#include <assert.h>
// #include <stdio.h>

int dirToInt(Direction dir);
#define TOP_FLOOR (N_FLOORS -1)
#define GROUND_FLOOR 0

typedef struct Level
{
    bool up;
    bool down;
} Level;

static Level levels[N_FLOORS];

void initBookings()
{
    clearAllBookings();
}

void clearBooking(int floor)
{
    assert(floor >= 0);
    assert(floor < N_FLOORS);
    levels[floor].up = false;
    levels[floor].down = false;
}

void clearAllBookings()
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        clearBooking(floor);
    }
}

void setBooking(int floor, Direction dir)
{
    assert(floor >= 0);
    assert(floor < N_FLOORS);
    switch (dir)
    {
    case UP:
        levels[floor].up = true;
        /* if (floor == 0)
        {
            levels[floor].down = true;
        } */
        break;
    case DOWN:
        levels[floor].down = true;
        /* if (floor == N_FLOORS-1)
        {
            levels[floor].up = true;
        } */
        break;
    case NONE:
        levels[floor].up = true;
        levels[floor].down = true;
        break;
    default:
        break;
    }
}

bool checkFloorBooking(int floor, Direction dir)
{
    assert(floor >= 0);
    assert(floor < N_FLOORS);
    switch (dir)
    {
    case UP:
        return levels[floor].up;

    case DOWN:
        return levels[floor].down;
    case NONE:
        assert(-1);
        break;
    }
    return false;
}

int getNextDestination(int currentFloor, Direction dir)
{
    assert(dir != NONE);
    int floor = currentFloor;

    // Øverste og nederste etasje har bare en retning
    if (currentFloor == TOP_FLOOR)
    {
        dir = DOWN;
    }
    else if (currentFloor == GROUND_FLOOR)
    {
        dir = UP;
    }

    Direction originalDir = dir;

    do
    {
        if(checkFloorBooking(floor,dir))
        {
            return floor;
        }

        floor += dirToInt(dir);

        if (floor == TOP_FLOOR || floor == GROUND_FLOOR)
        {
            dir = dir == UP ? DOWN : UP;    //endrer retning dersom vi når øverste eller nederste etasje
        }


    } while (!(currentFloor==floor && originalDir == dir));


    return NO_BOOKINGS;
}


int dirToInt(Direction dir)
{
    return dir==UP?1:-1;
}


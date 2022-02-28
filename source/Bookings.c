#include "Bookings.h"
#include "elevatorEnums.h"
#include <stdbool.h>
#include "driver/elevio.h"
#include <assert.h>
#include <stdio.h>

int directionToInt(Direction dir);

typedef struct Level
{
    bool up;
    bool down;
} Level;

static Level levels[N_FLOORS];

void initBookings()
{
    clearAllLevels();
}

void clearLevel(int floor)
{
    assert(floor >= 0);
    assert(floor < N_FLOORS);
    levels[floor].up = false;
    levels[floor].down = false;
}

void clearAllLevels()
{
    for (int floor = 0; floor < N_FLOORS; floor++)
    {
        clearLevel(floor);
    }
}

//Veldig dårlig kode
void checkBookings()
{
    // Les av knapper og legg inn booking
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            if (elevio_callButton(f, b) == 1) // enten 0 eller 1
            {
                setBooking(f,b);
            }
        }
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
        if (floor == 0)
        {
            levels[floor].down = true;
        }
        break;
    case DOWN:
        levels[floor].down = true;
        if (floor == N_FLOORS-1)
        {
            levels[floor].up = true;
        }
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

/*bool checkNextDestination(int currentFloor, Direction dir)
{
    switch (dir)
    {
    case UP:
        for (int i = currentFloor +1; i < N_FLOORS; i++)
        {
            if (levels[i].up)
            {
                return true;
            }
        }
        
        break;
    case DOWN:
        for (int i = currentFloor -1; i >= 0; i--)
        {
            if (levels[i].down)
            {
                return true;
            }
        }
        break;
    case NONE:
        return false;
        break;
    default:
        break;
    }
    return false;
}
*/

int getNextDestination(int currentFloor, Direction dir)
{
    assert(dir != NONE);
    // if (checkFloorBooking(currentFloor, dir))
    // {
    //     return currentFloor;
    // } Sletter ikke sin egen booking dersom det er flere bookings
    

    if (((currentFloor >= N_FLOORS-2) && (dir == UP)) || ((currentFloor<=1) && (dir==DOWN)))
    {
        dir = dir == UP ? DOWN : UP; //bytter retning hvis øverst eller nederst
    }
    int floor = currentFloor + directionToInt(dir); //begynner å sjekke fra etasjen over/under
    Direction originalDir = dir;


    while (!(floor == currentFloor && dir == originalDir))
    {
        if(checkFloorBooking(floor,dir))
        {
            return floor;
        }

        floor += directionToInt(dir);

        if (floor == N_FLOORS-1 || floor == 0)
        {
            dir = dir == UP ? DOWN : UP;
        }

    }

/*
    switch (dir)
    {
    case UP:
        for (int i = currentFloor+1; i < N_FLOORS; i++)
        {
            if (levels[i].up)
            {
                return i;
            }
        }
        
        break;
    case DOWN:
        for (int i = currentFloor-1; i >= 0; i--)
        {
            if (levels[i].down)
            {
                return i;
            }
        }
        break;
    case NONE:
        break;
    default:
        break;
    }
*/
    return currentFloor;
}


int directionToInt(Direction dir)
{
    return dir==UP?1:-1;
}


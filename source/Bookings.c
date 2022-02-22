#include "Bookings.h"
#include <stdbool.h>
#include "driver/elevio.h"
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
    levels[floor].up = false;
    levels[floor].down = false;
}

void clearAllLevels()
{
    for (int floor = 0; floor < sizeof(levels); floor++)
    {
        clearLevel(floor);
    }
}

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

void setBooking(int floor, int button)
{
    switch (button)
    {
    case BUTTON_HALL_UP:
        levels[floor].up = true;
        break;
    case BUTTON_HALL_DOWN:
        levels[floor].down = true;
        break;
    case BUTTON_CAB:
        levels[floor].up = true;
        levels[floor].down = true;
        break;
    default:
        break;
    }
}
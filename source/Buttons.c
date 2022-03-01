#include "Buttons.h"
#include "driver/elevio.h"

bool isButtonPressed(int floor, Direction dir)
{
    switch (dir)
    {
    case UP:
        return elevio_callButton(floor, BUTTON_HALL_UP);
    case DOWN:
        return elevio_callButton(floor, BUTTON_HALL_DOWN);
    case NONE:
        return elevio_callButton(floor, BUTTON_CAB);
    default:
        break;
    }
}

bool isObstructed()
{
    return elevio_obstruction();
}

bool isStopPressed()
{
    return elevio_stopButton();
}


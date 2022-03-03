#include "Motor.h"
#include "driver/elevio.h"

void initMotor()
{
    elevio_init();
}

void move(Direction dir)
{
    switch (dir)
    {
    case UP:
        elevio_motorDirection(DIRN_UP);
        break;
    case DOWN:
        elevio_motorDirection(DIRN_DOWN);
        break;
    case NONE:
        elevio_motorDirection(DIRN_STOP);
        break;
    default:
        break;
    }
}
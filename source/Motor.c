#include "Motor.h"
#include "driver/elevio.h"

void initMotor()
{
    elevio_init();
    findFloor();
}
void findFloor()
{
    
    //Midlertidig til Motormodul er lagd
    while (elevio_floorSensor() == -1)
    {
        elevio_motorDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);
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
    case STOP:
        elevio_motorDirection(DIRN_STOP);
        break;
    default:
        break;
    }
}
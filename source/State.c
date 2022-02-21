#include "driver/elevio.h"
#include "State.h"



typedef struct State {
    int lastFloor;
    Action action;
    Direction direction;
} State;

static State t = {-1,STOP_BETWEEN,DOWN};

void initState()
{
    setAction(STOP_FLOOR);
    updateLastFloor();
    return;
}

void updateLastFloor() {
    int floor = elevio_floorSensor();
    if (floor != -1){
        t.lastFloor = floor;
    }
    return;
}
int getLastFloor(){
    return t.lastFloor;
}
Action getAction()
{
    return t.action;
}
Direction getDirection()
{
    return t.direction;
}

void setDirection(Direction dir)
{
    t.direction = dir;
    return;
}

void setAction(Action a)
{
    t.action = a;
    return;
}
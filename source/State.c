#include "driver/elevio.h"
#include "State.h"



typedef struct OrtState {
    int lastFloor;
    Direction direction;
} OrtState;

static OrtState t = {-1,DOWN};


void initOrtState()
{
    //setAction(STOP_FLOOR);
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

Direction getDirection()
{
    return t.direction;
}

void setDirection(Direction dir)
{
    t.direction = dir;
    return;
}

Action getAction()
{
    //return t.action;
}

void setAction(Action a)
{
    //t.action = a;
    return;
}
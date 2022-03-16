#include "ElevatorControl.h"
#include "State.h"
#include "Motor.h"
#include "Lights.h"
#include "Bookings.h"
#include "Buttons.h"
#include "Timer.h"

void updateFloorPanel();

void initElevator()
{
    initMotor();
    initBookings();
    initLights();
    resetTimer();
}


typedef enum StateCode
{
    entry,
    stopFloor,
    moving,
    stopBetween,
    doorOpen
} StateCode;

static StateCode (* state[])(void) = {
    entryState,
    stopFloorState,
    movingState,
    stopBetweenState,
    doorOpenState
};


StateCode entryState(void)
{
    if (getFloor() == -1)
    {
        move(DOWN);
        return entry;
    }
    move(NONE);
    updateLastFloor();
    return stopFloor;
}


StateCode doorOpenState()
{
    setDoorLight();

    if (isStopPressed())
    {
        setStopLamp();
        clearAllBookings();
        clearAllButtonLamps();
        resetTimer();
        return doorOpen;
    }
    updateFloorPanel();

    int lastFloor = getLastFloor();
    clearButtonLamps(lastFloor);
    clearBooking(lastFloor);
    clearStopLamp();

    if (isObstructed())
    {
        resetTimer();
        return doorOpen;
    }

    if (checkTimer(3))
    {
        clearDoorLight();
        resetTimer();
        return stopFloor;
    }
    return doorOpen;
}

StateCode stopFloorState(void)
{
    if (isStopPressed())
    {
        return moving;
    }
    updateFloorPanel();

    //Oppdater bestillinger
    //Sletter bestilling i etasjen (så lenge døra er åpen)
    if (getNextDestination(getLastFloor(), getDirection()) != NO_BOOKINGS)
    {
        return moving;
    }
    return stopFloor;


}

StateCode movingState(void)
{
    updateFloorPanel();

    int floor = getFloor();
    int lastFloor = getLastFloor();
    int direction = getDirection();
    int nextFloor = getNextDestination(lastFloor, direction);

    updateLastFloor();

    if (isStopPressed())
    {
        move(NONE);
        return stopBetween;
    }

    if (nextFloor < lastFloor)
    {
        setDirection(DOWN);
    }
    if (nextFloor > lastFloor)
    {
        setDirection(UP);
    }
    if(nextFloor == floor)
    {
        move(NONE);
        resetTimer();
        return doorOpen;
    }
    /*
    if (nextFloor == lastFloor)
    {
        // Om destinasjonen er forrige etasje, må heisen gå i motsatt retning
        swapDirection();
        move(getDirection());
        swapDirection();
        return motion;
    }*/

    move(getDirection());
    return moving;
}

StateCode stopBetweenState(void)
{
    if (isStopPressed())
    {
        setStopLamp();
        clearAllBookings();
        clearAllButtonLamps();
        return stopBetween;
    }
    clearStopLamp();
    updateFloorPanel();
    //wait for next booking
    int lastFloor = getLastFloor();
    int direction = getDirection();
    int nextFloor = getNextDestination(lastFloor, direction);

    if (nextFloor == NO_BOOKINGS)
    {
        return stopBetween;
    }

    return moving;
}

void updateFloorPanel()
{
    for (int floor = 0; floor < numFloors(); floor++)
    {
        for (int dir = 0; dir < NUM_DIRECTIONS; dir++)
        {
            if (isButtonPressed(floor, dir))
            {
                setButtonLamp(floor, dir);
                setBooking(floor, dir);
            }
        }
    }
    setFloorIndicator(getLastFloor());
}



void runElevator()
{
    initElevator();

    StateCode currentState = entry;
    StateCode (* stateFunction)(void);

    while(1)
    {
        stateFunction = state[currentState];
        currentState = stateFunction();
    }
}





//https://stackoverflow.com/questions/1371460/state-machines-tutorials/1371829
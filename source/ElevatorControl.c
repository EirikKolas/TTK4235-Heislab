#include "ElevatorControl.h"
#include "State.h"
#include "Motor.h"
#include "Lights.h"
#include "Bookings.h"
#include "Buttons.h"
#include "Timer.h"


//Definerer statePtr som en peker til en funksjon som tar inn 0 parameter 
//og returnerer en statePtr
typedef void (*_funcPtr) (void);
typedef _funcPtr (*statePtr) (void);

void initElevator()
{
    initMotor();
    initBookings();
    initLights();
    resetTimer();
}

statePtr entryState(void)
{
    if (getFloor() == -1)
    {
        move(DOWN);
        return entryState;
    }
    move(NONE);
    updateLastFloor();
    return stopFloorState;
}


statePtr doorOpenState()
{
    setDoorLight();

    if (isStopPressed())
    {
        setStopLamp();
        clearAllBookings();
        clearAllButtonLamps();
        resetTimer();
        return doorOpenState;
    }
    updateFloorPanel();

    int lastFloor = getLastFloor();
    clearButtonLamps(lastFloor);
    clearBooking(lastFloor);
    clearStopLamp();

    if (isObstructed())
    {
        resetTimer();
        return doorOpenState;
    }

    if (checkTimer(3))
    {
        clearDoorLight();
        resetTimer();
        return stopFloorState;
    }
    return doorOpenState;
}

statePtr stopFloorState(void)
{
    if (isStopPressed())
    {
        return movingState;
    }
    updateFloorPanel();

    //Oppdater bestillinger
    //Sletter bestilling i etasjen (så lenge døra er åpen)
    if (getNextDestination(getLastFloor(), getDirection()) != NO_BOOKINGS)
    {
        return movingState;
    }
    return stopFloorState;


}

statePtr movingState(void)
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
        return stopBetweenState;
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
        return doorOpenState;
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
    return movingState;
}

statePtr stopBetweenState(void)
{
    if (isStopPressed())
    {
        setStopLamp();
        clearAllBookings();
        clearAllButtonLamps();
        return stopBetweenState;
    }
    clearStopLamp();
    updateFloorPanel();
    //wait for next booking
    int lastFloor = getLastFloor();
    int direction = getDirection();
    int nextFloor = getNextDestination(lastFloor, direction);

    if (nextFloor == NO_BOOKINGS)
    {
        return stopBetweenState;
    }

    return movingState;
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

    statePtr state = entryState;

    while(1)
    {
        state = state();
    }
}





//https://stackoverflow.com/questions/1371460/state-machines-tutorials/1371829
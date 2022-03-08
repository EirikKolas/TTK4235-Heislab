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
    printf("=== Oskar er ikke pen ===\n");
}


typedef enum StateCodes {entry, stopFloor, moving, stopBetween, doorOpen} StateCodes;
typedef enum Trigger {motion, stop, reachedFloor} Trigger;


Trigger entryState(void)
{
    if (getFloor() == -1)
    {
        move(DOWN);
        return motion;
    }
    move(NONE);
    updateLastFloor();
    return reachedFloor;
}


Trigger doorOpenState()
{
    setDoorLight();

    if (isStopPressed())
    {
        setStopLamp();
        clearAllBookings();
        clearAllButtonLamps();
        resetTimer();
        return stop;
    }
    updateFloorPanel();

    int lastFloor = getLastFloor();
    clearButtonLamps(lastFloor);
    clearBooking(lastFloor);
    clearStopLamp();

    if (isObstructed())
    {
        resetTimer();
        return stop;
    }

    if (checkTimer(3))
    {
        clearDoorLight();
        resetTimer();
        return reachedFloor;
    }
    return stop;
}

Trigger stopFloorState(void)
{
    if (isStopPressed())
    {
        return stop;
    }
    updateFloorPanel();

    //Oppdater bestillinger
    //Sletter bestilling i etasjen (så lenge døra er åpen)
    if (getNextDestination(getLastFloor(), getDirection()) != NO_BOOKINGS)
    {
        return motion;
    }
    return reachedFloor;


}

Trigger movingState(void)
{
    updateFloorPanel();
    updateLastFloor();

    int floor = getFloor();
    int lastFloor = getLastFloor();
    int direction = getDirection();
    int nextFloor = getNextDestination(lastFloor, direction);


    if (isStopPressed())
    {
        move(NONE);
        return stop;
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
        return reachedFloor;
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
    return motion;
}

Trigger stopBetweenState(void)
{
    if (isStopPressed())
    {
        setStopLamp();
        clearAllBookings();
        clearAllButtonLamps();
        return stop;
    }
    clearStopLamp();
    updateFloorPanel();
    //wait for next booking
    int lastFloor = getLastFloor();
    int direction = getDirection();
    int nextFloor = getNextDestination(lastFloor, direction);

    if (nextFloor == NO_BOOKINGS)
    {
        return stop;
    }

    return motion;
}

static Trigger (* state[])(void) = {
    entryState,
    stopFloorState,
    movingState,
    stopBetweenState,
    doorOpenState
};


struct Transition
{
    enum StateCodes currentState;
    enum Trigger trig;
    enum StateCodes destinationState;
};

static struct Transition stateTransitions[] =
{
    {entry,       reachedFloor, stopFloor},
    {entry,       motion,       entry},
    {stopFloor,   motion,       moving},
    {stopFloor,   stop,         doorOpen},
    {stopFloor,   reachedFloor, stopFloor},
    {moving,      stop,         stopBetween},
    {moving,      motion,       moving},
    {moving,      reachedFloor, doorOpen},
    {stopBetween, motion,       moving},
    {stopBetween, stop,         stopBetween},
    {doorOpen,    stop,         doorOpen},
    {doorOpen,    reachedFloor, stopFloor}
};

StateCodes lookupTransitions(StateCodes s, Trigger t)
{
    for (int i = 0; i < sizeof(stateTransitions)/sizeof(stateTransitions[0]); i++)
    {
        if (stateTransitions[i].currentState == s && stateTransitions[i].trig == t)
        {
            return stateTransitions[i].destinationState;
        }
    }
    return s;
}


void runElevator()
{
    initElevator();

    StateCodes currentState = entry;
    Trigger trig;
    Trigger (* stateFunction)(void);

    while(1)
    {
        stateFunction = state[currentState];
        trig = stateFunction();
        currentState = lookupTransitions(currentState, trig);

    }
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


//https://stackoverflow.com/questions/1371460/state-machines-tutorials/1371829
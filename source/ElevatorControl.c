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
    initOrtState();
    initBookings();
    initLights();
    resetTimer();
    printf("=== Example Program ===\n");
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
}


typedef enum StateCodes {entry, stopFloor, moving, stopBetween, doorOpen} StateCodes;
typedef enum Trigger {motion, stop, reachedFloor} Trigger;


Trigger entryState(void) 
{
    initElevator();
    return reachedFloor;
}


Trigger doorOpenState()
{
    updateFloorPanel();
    setDoorLight();
    updateTimer();

    int floor = getFloor();
    clearButtonLamps(floor);
    clearBooking(floor);


    if (isStopPressed())
    {
        setStopLamp();
        clearAllBookings();
        clearAllButtonLamps();
        resetTimer();
        return stop;
    }
    clearStopLamp();

    if (isObstructed())
    {
        resetTimer();
        return stop;
    }
    
    if (checkTimer(1000))
    {
        clearDoorLight();
        resetTimer();
        return reachedFloor;
    }
    return stop;
}


Trigger stopFloorState(void)
{
    updateFloorPanel();
    int floor = getFloor();
    int direction = getDirection();

    if (isStopPressed())
    {
        return stop;
    }
    //Oppdater bestillinger
    //Sletter bestilling i etasjen (så lenge døra er åpen)
    if (getNextDestination(floor, direction) != NO_BOOKINGS)
    {
        return motion;
    }
    return reachedFloor;
    

}
Trigger movingState(void)
{
    int floor = getFloor();
    int lastFloor = getLastFloor();
    int direction = getDirection();
    int nextFloor = getNextDestination(lastFloor, direction);

    updateLastFloor();
    updateFloorPanel();

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
        return reachedFloor;
    }
    move(getDirection());
    return motion;
}
Trigger stopBetweenState(void)
{
    updateFloorPanel();
    if (isStopPressed())
    {
        setStopLamp();
        clearAllBookings();
        clearAllButtonLamps();
        return stop;
    }
    clearStopLamp();
    //wait for next booking
    int lastFloor = getLastFloor();
    int direction = getDirection();
    int nextFloor = getNextDestination(lastFloor, direction);

    if (nextFloor == NO_BOOKINGS)
    {
        return stop;
    }
    if (nextFloor == lastFloor)
    {
        swapDirection();
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

//https://stackoverflow.com/questions/1371460/state-machines-tutorials/1371829

void runElevator() 
{
    StateCodes currentState = entry;
    Trigger trig;
    Trigger (* stateFunction)(void);

    while(1)
    {
        stateFunction = state[currentState];
        trig = stateFunction();
        currentState = lookupTransitions(currentState, trig);
        
        //midlertidig exit
        /*if(elevio_stopButton())
        {
            move(NONE);
            elevio_stopLamp(1);
            break;
        }*/
        sleep();
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
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"              //Skal fjernes
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


typedef enum StateCodes {entry, stopFloor, moving, stopBetween} StateCodes;
typedef enum Trigger {motion, stop, reachedFloor} Trigger;


Trigger entryState(void) 
{
    initElevator();
    return reachedFloor;
}
//Lag open door state, løser jeg vil inn i heisen igjen og party lys
Trigger stopFloorState(void)
{
    updateTimer();
    updateFloorPanel();
    int floor = getFloor();
    int direction = getDirection();

    setDoorLight();

    if (isStopPressed())
    {
        setStopLamp();
        clearAllBookings();
        clearAllButtonLamps();
    }
    else
    {
        clearStopLamp();
    }

    if (isObstructed() || isStopPressed())
    {
        resetTimer();
        return stop;
    }
    else if (checkTimer(1000))
    {
        clearDoorLight();
    }
    else
    {
        return stop;
    }
    //Oppdater bestillinger
    //Sletter bestilling i etasjen (så lenge døra er åpen)
    clearButtonLamps(floor);
    clearBooking(floor);
    if (getNextDestination(floor, direction) != NO_BOOKINGS)
    {
        resetTimer();
        return motion;
    }
    return stop;
    

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
    stopBetweenState
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
    {stopFloor,   stop,         stopFloor},
    {moving,      stop,         stopBetween},
    {moving,      motion,       moving},
    {moving,      reachedFloor, stopFloor},
    {stopBetween, motion,       moving},
    {stopBetween, stop,         stopBetween}
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
    //updateLastFloor();
    //int floor = getLastFloor();
    //int nextFloor = getNextDestination(floor,getDirection());
/*
    while(1)
    {
    //Check og print floor
        updateLastFloor();
        floor = getLastFloor();
        elevio_floorIndicator(floor);       // må være initiert (dvs ikke -1)
        //printf("floor: %d \n",floor);

    //Oppdater bestillinger
        checkBookings();
        printf("next floor: %d \n",nextFloor);

    //Bevegelse til etasjer
        if(floor == nextFloor){
            move(NONE);
            clearLevel(floor);
            nextFloor = getNextDestination(floor,getDirection());
        }

        if(floor < nextFloor){
            move(UP);
            printf("Up: %d \n",UP);
            setDirection(UP);
        }

        if(floor > nextFloor){
            move(DOWN);
            printf("Down: %d \n",DOWN);
            setDirection(DOWN);
        }

    //Les av knapper og slå på lys
        activateButtonLamps();
        deactivateButtonLamps(floor);       // legg til if setning, getAction == stop_floor
        
    //Sjekk obstruction og stopknapp    STOP = 2
        if (elevio_obstruction())
        {
            elevio_stopLamp(1);
        }
        else
        {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            move(NONE);
            elevio_stopLamp(1);
            break;
        }

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
*/


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
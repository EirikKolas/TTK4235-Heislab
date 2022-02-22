#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "ElevatorControl.h"
#include "State.h"
#include "Motor.h"
#include "Lights.h"
#include "Bookings.h"
#include "driver/elevio.h"              //Skal fjernes


void initElevator()
{
    initMotor();
    initOrtState();
    initBookings();
    initLights();
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
}
void runElevator() 
{
    move(UP);

    while(1){
    //Check og print floor
        updateLastFloor();
        int floor = getLastFloor();
        elevio_floorIndicator(floor);       // må være initiert (dvs ikke -1)
        printf("floor: %d \n",floor);

        if(floor == 0){
            move(UP);
        }

        if(floor == N_FLOORS-1){
            move(DOWN);
        }

    //Les av knapper og slå på lys
        activateButtonLamps();
        deactivateButtonLamps(floor);       // legg til if setning, getAction == stop_floor
        
    //Sjekk obstruction og stopknapp    STOP = 2
        
        if(elevio_stopButton()){
            move(STOP);
            break;
        }
    //Les av og utv

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

}


typedef enum StateCodes {entry, stopFloor, moving, stopBetween} StateCodes;
typedef enum Trigger {motion, stop, reachedFloor} Trigger;


int entryState(void) 
{
    initElevator();
    return reachedFloor;
}

int stopFloorState(void)
{
    //openDoor() hvis dør ikke åpen
    //checkOstruction()
    //checkStop()
    //closeDoor(if 3 sec and no bestilling);
    //if (doorClosed())
        //sjekk ny bestilling
        //hent ny bestilling
        //oppdater retning om nødvendig
        //return move
    return stop;
    

}
int movingState(void)
{
    //finn bov) return stop;
    return motion;
}
int stopBetweenState(void)
{
    clearAllLevels();
    //if (booking & !stop) return move;
    //return stop;
}

int (* state[])(void) = {
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
    for (int i = 0; i < sizeOf(stateTransitions); i++)
    {
        if (stateTransitions[i].currentState == s && stateTransitions[i].trig == t)
        {
            return stateTransitions[i].destinationState;
        }  
    }
    return s;
}
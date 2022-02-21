#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "ElevatorControl.h"
#include "State.h"
#include "Motor.h"
#include "Lights.h"
#include "driver/elevio.h"              //Skal fjernes


void initElevator()
{
    initMotor();
    initState();
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
        
    //Sjekk obstruction og stopknapp
        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            move(STOP);
            break;
        }
    //Les av og utfør bestillinger


        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

}
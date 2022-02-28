#include "Lights.h"
#include "driver/elevio.h"
#include "State.h"

void activateButtonLamps()
{
    // Les av knapper og slå på lys
    for (int f = 0; f < N_FLOORS; f++)
    {
        for (int b = 0; b < N_BUTTONS; b++)
        {
            if (elevio_callButton(f, b) == 1) // enten 0 eller 1
            {
                elevio_buttonLamp(f, b, 1);
            }
        }
    }
}
void deactivateButtonLamps(int floor)
{
    for (int b = 0; b < N_BUTTONS; b++)
    {
        elevio_buttonLamp(floor, b, 0);
    }
    elevio_stopLamp(0);
}
void initLights()
{
    for (int f = 0; f < N_FLOORS; f++)
    {
        deactivateButtonLamps(f);
    }
}
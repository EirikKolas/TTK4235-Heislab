#include "Lights.h"
#include "driver/elevio.h"

ativateButtonLamps()
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

void setButtonlamp(int floor, Direction dir, bool value)
{
    switch (dir)
    {
    case UP:
        elevio_buttonLamp(floor, BUTTON_HALL_UP, value);
        break;
    case DOWN:
        elevio_buttonLamp(floor, BUTTON_HALL_DOWN, value);
        break;
    case NONE:
        elevio_buttonLamp(floor, BUTTON_CAB, value);
        break;
    default:
        break;
    }
}
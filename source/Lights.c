#include "Lights.h"
#include "driver/elevio.h"

/*
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
}*/
void modifyButtonLamp(int floor, Direction dir, bool btnPressed);

void clearButtonLamps(int floor)
{
    modifyButtonLamp(floor,UP,0);
    modifyButtonLamp(floor,DOWN,0);
    modifyButtonLamp(floor,NONE,0);
}
void clearAllButtonLamps()
{
    for (int f = 0; f < N_FLOORS; f++)
    {
        clearButtonLamps(f);
    }
}
void initLights()
{
    clearAllButtonLamps();
    clearStopLamp();
    clearDoorLight();
}

void modifyButtonLamp(int floor, Direction dir, bool btnPressed)
{
    switch (dir)
    {
    case UP:
        elevio_buttonLamp(floor, BUTTON_HALL_UP, btnPressed);
        break;
    case DOWN:
        elevio_buttonLamp(floor, BUTTON_HALL_DOWN, btnPressed);
        break;
    case NONE:
        elevio_buttonLamp(floor, BUTTON_CAB, btnPressed);
        break;
    default:
        break;
    }
}
void setButtonLamp(int floor, Direction dir)
{
    modifyButtonLamp(floor, dir, 1);
}

void setFloorIndicator(int floor)
{
    elevio_floorIndicator(floor);
}

void setDoorLight()
{
    elevio_doorOpenLamp(1);
}

void clearDoorLight()
{
    elevio_doorOpenLamp(0);
}

void setStopLamp()
{
    elevio_stopLamp(1);
}

void clearStopLamp()
{
    elevio_stopLamp(0);
}
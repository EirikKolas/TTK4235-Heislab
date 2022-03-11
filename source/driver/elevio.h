/**
* @file
* @brief Hardware functions that are unique to this elevator system.
*/

#pragma once
#define N_FLOORS 4

/**
* @brief Motor direction enum with the directions @p DIRN_DOWN , @p DIRN_STOP and @p DIRN_UP .
*/
typedef enum { 
    DIRN_DOWN   = -1, /* Direction down */
    DIRN_STOP   = 0,  /* Direction down */
    DIRN_UP     = 1   /* Direction down */
} MotorDirection;


#define N_BUTTONS 3

/**
* @brief Elevator button enum with the buttons @p BUTTON_HALL_UP , @p DIRN_STOP and @p DIRN_UP .
*/
typedef enum { 
    BUTTON_HALL_UP      = 0, /* Up button on the outside of the elevator */
    BUTTON_HALL_DOWN    = 1, /* Down button on the outside of the elevator */
    BUTTON_CAB          = 2  /* Cab button inside the elevator to choose next floor*/
} ButtonType;

/**
* @brief Initializes the hardware.
*/
void elevio_init(void);

/**
* @brief Runs the motor in the specified direction @p dirn .
*
* @param[in] dirn Direction of which the motor is to be run.
*/
void elevio_motorDirection(MotorDirection dirn);

/**
* @brief Tuns on/off a light on a specified @p button at a specific @p floor based on the input @p value .
*
* @param[in] floor Floor where the button is located.
* @param[in] button Type of button whose light is to be turned on/off.
* @param[in] value Input value to determine on=1 or off=0.
*/
void elevio_buttonLamp(int floor, ButtonType button, int value);

/**
* @brief Sets the floor indicator lamp at a specific @p floor .
*
* @param[in] floor Elevator floor where the indicator lamp is to be set.
*/
void elevio_floorIndicator(int floor);

/**
* @brief Turns the door lamp on or off based on the input @p value .
*
* @param[in] value Value to determine on=1 or off=0.
*/
void elevio_doorOpenLamp(int value);

/**
* @brief Turns the stop lamp on or off based on the input @p value .
*
* @param[in] value Value to determine on=1 or off=0.
*/
void elevio_stopLamp(int value);

/**
* @brief Checks if a type of @p button is pressed at a specific @p floor .
*
* @param[in] floor Elevator floor where the button is located.
* @param[in] button Type of button to be checked.
*
* @return 1 (true) if the button is pressed and 0 (false) if it is not pressed.
*/
int elevio_callButton(int floor, ButtonType button);

/**
* @brief Checks which floor the elevator is at.
*
* @return returns the floor where the elevator is located, and -1 if the elevator is between floors.
*/
int elevio_floorSensor(void);

/**
* @brief Checks if the stop button is pressed.
*
* @return 1 (true) if the stop button is pressed, and 0 (false) if not.
*/
int elevio_stopButton(void);

/**
* @brief Checks if obstruction is active.
*
* @return 1 (true) if obstruction is active, and 0 (false) if not.
*/
int elevio_obstruction(void);


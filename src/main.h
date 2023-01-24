#include <stdint.h>
#include <Arduino.h>
#include <stepper_controller.h>

#define COIL_1 33
#define COIL_2 32
#define COIL_3 35
#define COIL_4 34

enum VENDING_STATE {
    POLLING,
    MOTOR_FORWARD,
    SERVO_ON,
    SERVO_OFF,
    MOTOR_BACKWARD,
};

VENDING_STATE state;
VENDING_STATE next_state;

void state_machine_poll();
VENDING_STATE poll_input();
VENDING_STATE drive_motor();
VENDING_STATE drive_servo();

uint8_t bin_buttons = 0b000;

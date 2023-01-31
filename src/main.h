#include <stdint.h>
#include <Arduino.h>
#include <stepper_controller.h>

#define COIL_1 33
#define COIL_2 32
#define COIL_3 35
#define COIL_4 34

#define SERVO_PIN_1 13
#define SERVO_PIN_2 12
#define SERVO_FREQUENZY 50
#define SERVO_CHANNEL_1 0
#define SERVO_CHANNEL_2 1
#define SERVO_RESOLUTION 16

#define MOTOR_DRIVE_TIME_MULTIPLIER 5*1000

enum VENDING_STATE {
    POLLING,
    MOTOR_FORWARD,
    DRIVE_SERVO,
    MOTOR_BACKWARD,
};

VENDING_STATE state;
VENDING_STATE next_state = POLLING;

void state_machine_poll();
VENDING_STATE poll_input();
VENDING_STATE drive_motor();

uint8_t bin_buttons = 0b000;

#include "main.h"

StepperController stepper_controller = StepperController(COIL_1, COIL_2, COIL_3, COIL_4);


VENDING_STATE poll_input() {

  return POLLING;
}

VENDING_STATE drive_motor(STEP_DIRECTION direction) {

  u_int64_t end_time = millis() + (bin_buttons * MOTOR_DRIVE_TIME_MULTIPLIER);

  while (end_time > millis())
  {
    stepper_controller.Step(direction);    
    delay(1);
  }
  
  if (direction == CLOCKWISE)
  {
    return DRIVE_SERVO;
  }
  
  return POLLING;
}

VENDING_STATE drive_servo() {
  
  return MOTOR_BACKWARD;
}

void state_machine_poll() {
  state = next_state;
  switch (state)
  {
  case POLLING: next_state=poll_input(); break;
  case MOTOR_FORWARD: next_state=drive_motor(CLOCKWISE); break;
  case DRIVE_SERVO: next_state=drive_servo(); break;
  case MOTOR_BACKWARD: next_state=drive_motor(COUNTERCLOCKWISE); break;
  default: next_state = POLLING; break;
  }
}


void setup() {

}

void loop() {
  state_machine_poll();
}
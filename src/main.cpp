#include "main.h"


VENDING_STATE poll_input() {

}

VENDING_STATE motor_forward() {

}

VENDING_STATE motor_backward() {

}

VENDING_STATE servo_on() {

}

VENDING_STATE servo_off() {
  
}

void state_machine_poll() {
  state = next_state;
  switch (state)
  {
  case POLLING: next_state=POLLING; break;
  default:
    break;
  }
}

StepperController stepper_controller = StepperController(COIL_1, COIL_2, COIL_3, COIL_4);

void setup() {
  stepper_controller.MoveSteps(5, COUNTERCLOCKWISE);
}

void loop() {
  delayMicroseconds(1000);
	stepper_controller.Step(COUNTERCLOCKWISE);
}
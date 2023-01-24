#include "main.h"

int servoPin_1 = 13;
int servoPin_2 = 12;
int freq = 50;
int channel_1 = 0;
int channel_2 = 1;
int resolution = 16;


VENDING_STATE poll_input() {

}

VENDING_STATE motor_forward() {

}

VENDING_STATE motor_backward() {

}

VENDING_STATE servo_1() {
    ledcWrite(channel_1, 3277);
    delay(1000);
    ledcWrite(channel_1, 6553);
}

VENDING_STATE servo_2() {
    ledcWrite(channel_2, 3277);
    delay(1000);
    ledcWrite(channel_2, 6553);
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
  ledcSetup(channel_1, freq, resolution);
  ledcSetup(channel_2, freq, resolution);

  ledcAttachPin(servoPin_1, channel_1);
  ledcAttachPin(servoPin_2, channel_2);
  
  stepper_controller.MoveSteps(5, COUNTERCLOCKWISE);
}

void loop() {
  delayMicroseconds(1000);
	stepper_controller.Step(COUNTERCLOCKWISE);
}
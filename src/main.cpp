#include "main.h"

int servoPin_1 = 13;
int servoPin_2 = 12;
int freq = 50;
int channel_1 = 0;
int channel_2 = 1;
int resolution = 16;

StepperController stepper_controller = StepperController(COIL_1, COIL_2, COIL_3, COIL_4);

VENDING_STATE poll_input() {
  //reads state of Start Button
  int startButtonCurrState = digitalRead(14);
  int tipSwich01CurrState = digitalRead(18);
  int tipSwich02CurrState = digitalRead(19);
  int tipSwich03CurrState = digitalRead(23);

  return POLLING;
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

VENDING_STATE servo_off() {
  
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
  ledcSetup(channel_1, freq, resolution);
  ledcSetup(channel_2, freq, resolution);

  ledcAttachPin(servoPin_1, channel_1);
  ledcAttachPin(servoPin_2, channel_2);
  
  stepper_controller.MoveSteps(5, COUNTERCLOCKWISE);
}
void loop() {
  state_machine_poll();
}

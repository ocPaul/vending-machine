#include <Arduino.h>
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

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
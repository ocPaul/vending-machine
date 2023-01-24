#include <Arduino.h>
#include <stepper_controller.h>

#define COIL_1 33
#define COIL_2 32
#define COIL_3 35
#define COIL_4 34

StepperController stepper_controller = StepperController(COIL_1, COIL_2, COIL_3, COIL_4);

void setup() {
  stepper_controller.MoveSteps(5, COUNTERCLOCKWISE);
}

void loop() {
  delayMicroseconds(1000);
	stepper_controller.Step(COUNTERCLOCKWISE);
}
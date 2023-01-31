#include "main.h"

StepperController stepper_controller = StepperController(COIL_1, COIL_2, COIL_3, COIL_4);


VENDING_STATE poll_input() {
  //reads state of Start Button
  int startButtonCurrState = digitalRead(14);
  int tipSwich01CurrState = digitalRead(18);
  int tipSwich02CurrState = digitalRead(19);
  int tipSwich03CurrState = digitalRead(23);

  if (startButtonCurrState == LOW)
  {
    bin_buttons = 0b000;
    bin_buttons |= (tipSwich01CurrState == HIGH) ? 0b001 : 0;
    bin_buttons |= (tipSwich02CurrState == HIGH) ? 0b010 : 0;
    bin_buttons |= (tipSwich03CurrState == HIGH) ? 0b100 : 0;
    return MOTOR_FORWARD;
  }

  return POLLING;
}

void servo_1() {
    //rotates the servo connected to channel_1
    ledcWrite(SERVO_CHANNEL_1, 3277); //turns the servo to 90° clockwise
    delay(1000);
    ledcWrite(SERVO_CHANNEL_1, 6553); //turns the servo to 90° counterclockwise
}

void servo_2() {
    //rotats the servo of channel_2
    ledcWrite(SERVO_CHANNEL_2, 3277);
    delay(1000);
    ledcWrite(SERVO_CHANNEL_2, 6553);
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

void state_machine_poll() {
  state = next_state;
  Serial.println(state);
  switch (state)
  {
  case POLLING: next_state=poll_input(); break;
  case MOTOR_FORWARD: next_state=drive_motor(CLOCKWISE); break;
  case DRIVE_SERVO: next_state=MOTOR_BACKWARD; servo_1(); servo_2; break;
  case MOTOR_BACKWARD: next_state=drive_motor(COUNTERCLOCKWISE); break;
  default: next_state = POLLING; break;
  }
}


void setup() {
  pinMode(SERVO_PIN_1, OUTPUT);
  pinMode(SERVO_PIN_2, OUTPUT);

  pinMode(14, INPUT);
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(23, INPUT);
  
  ledcSetup(SERVO_CHANNEL_1, SERVO_FREQUENZY, SERVO_RESOLUTION);
  ledcSetup(SERVO_CHANNEL_2, SERVO_FREQUENZY, SERVO_RESOLUTION);

  ledcAttachPin(SERVO_PIN_1, SERVO_CHANNEL_1);
  ledcAttachPin(SERVO_PIN_2, SERVO_CHANNEL_2);


  Serial.begin(9600);
}
void loop() {
  state_machine_poll();
  int startButtonCurrState = digitalRead(14);
  int tipSwich01CurrState = digitalRead(18);
  int tipSwich02CurrState = digitalRead(19);
  int tipSwich03CurrState = digitalRead(23);
  delay(5000);
  Serial.println("-----------");
  Serial.println(startButtonCurrState);
  Serial.println(tipSwich01CurrState);
  Serial.println(tipSwich02CurrState);
  Serial.println(tipSwich03CurrState);
}

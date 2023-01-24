#include <Arduino.h>

void setup() {


  // initializes Start Button as Pull Up Input
  pinMode(14, INPUT_PULLUP);
  pinMode(18, INPUT_PULLDOWN);
  pinMode(19, INPUT_PULLDOWN);
  pinMode(23, INPUT_PULLDOWN);
}
void loop() {
  // put your main code here, to run repeatedly:

  //reads state of Start Button
  int startButtonCurrState = digitalRead(14);
  int tipSwich01CurrState = digitalRead(18);
  int tipSwich02CurrState = digitalRead(19);
  int tipSwich03CurrState = digitalRead(23);
}

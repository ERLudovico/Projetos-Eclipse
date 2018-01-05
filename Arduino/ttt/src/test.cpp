#include <Arduino.h>
#define WLED	13

void setup()
{
  pinMode(WLED, OUTPUT);  // set pin as output
}

void loop()
{
  digitalWrite(WLED, HIGH);  // set the LED on
  delay(3333);               // wait for a second
  digitalWrite(WLED, LOW);   // set the LED off
  delay(4444);               // wait for a second
}

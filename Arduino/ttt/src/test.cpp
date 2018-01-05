#include <Arduino.h>
#define WLED	13
int linux = 0;

void setup()
{
  pinMode(WLED, OUTPUT);  // set pin as output
}

void loop()
{
  digitalWrite(WLED, HIGH);  // set the LED on
  delay(200);               // wait for a second
  digitalWrite(WLED, LOW);   // set the LED off
  delay(2000);               // wait for a second
}

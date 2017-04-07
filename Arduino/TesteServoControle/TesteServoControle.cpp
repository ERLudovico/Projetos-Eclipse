#include <Arduino.h>
#include <RBD_Servo.h>
// Teste Linux to git 2
/* Refencia
 * http://robotsbigdata.com/docs-arduino-servo.html
 */
RBD::Servo servo(2, 1000, 2000); // pin 2, 1ms - 2ms pulse

void setup() {
  servo.moveToDegrees(90);
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
	digitalWrite(LED_BUILTIN, HIGH);
	servo.moveToDegrees(45);
	delay(500);
	digitalWrite(LED_BUILTIN, LOW);
	delay(1000);
	servo.moveToDegrees(120);
	servo.update();
}

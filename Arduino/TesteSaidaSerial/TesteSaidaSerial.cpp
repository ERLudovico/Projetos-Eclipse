#include <Arduino.h>
// Teste Linux to git


void setup() {
	Serial.begin(115200);
	//Serial.begin(57600);
	//Serial.begin(9600);
}
int n = 0;
void loop() {
	Serial.print("Ola");
	Serial.println(n++);
	delay(200);
}

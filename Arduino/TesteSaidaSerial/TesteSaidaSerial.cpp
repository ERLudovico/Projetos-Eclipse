#include <Arduino.h>

void setup() {
	Serial.begin(115200);
}
int n = 0;
void loop() {
	Serial.print("Ol�");
	Serial.println(n++);
	delay(200);
}
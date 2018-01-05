#include <Arduino.h>

#define cellPin1 A2
#define cellPin2 A3
#define cellPin3 A6
#define NumAmostras 100

/*
 * Veriaveis
 */


byte pinCell[] 			= {   A0,    A2,    A3,    A6 } ;
float volCell[] 		= { 0.00,  0.00,  0.00,  0.00 } ;
float volCellOffset[] 	= { 0.00, 11.68, 11.15, 11.45 } ;

/*
 * Declarando funcoes
 */
void sendSerialMessage();
void getVolCellPin();


void setup() {
	Serial.begin(9600);
}

void loop() {
	getVolCellPin();
	sendSerialMessage();
	delay(250);              // wait for a second
}

void getVolCellPin(){
	for (int c=1; c<=3 ;c++){
		float tempVolt = 0.00 ;
		for (int i=0; i<NumAmostras; i++){
			tempVolt += (analogRead(pinCell[c]) * (5.0 / 1023.0) );
		}
		tempVolt = tempVolt / NumAmostras ;
		volCell[c] = tempVolt * volCellOffset[c] ;
	}


	volCell[4]  = volCell[3];
	volCell[3] -= volCell[2];
	volCell[2] -= volCell[1];

}


void sendSerialMessage(){

	Serial.print("<");
	Serial.print("2");
	Serial.print(",");
	Serial.print(volCell[1]);
	Serial.print(",");
	Serial.print(volCell[2]);
	Serial.print(",");
	Serial.print(volCell[3]);
	Serial.print(",");
	Serial.print(volCell[4]);
	Serial.println(">");
}

#include <Arduino.h>

#define cellPin1 A2
#define cellPin2 A3
#define cellPin3 A6
#define NumAmostras 10

/*
 * Veriaveis
 */

int qtCell = 0 ;
byte pinCell[] 			= {   A0,    A2,    A3,    A6 } ;
float volCell1 = 0.00;
float volCell2 = 0.00;
float volCell3 = 0.00;
float volCellT = 0.00;
float volCell[] 		= { 0.00,  0.00,  0.00,  0.00, 0,00 } ;
float volCellOffset[] 	= { 0.00, 11.72, 10.90, 11.05 } ;
String serialTrain ;

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
	qtCell = 1 ;
	for (int c=1; c<=3 ;c++){
		float tempVolt = 0.00 ;
		for (int i=0; i<NumAmostras; i++){
			tempVolt += (analogRead(pinCell[c]) * (5.015 / 1023.0) );
		}
		tempVolt = tempVolt / NumAmostras ;
		volCell[c] = tempVolt * volCellOffset[c] ;
	}

	volCellT = volCell[3] ;
	volCell1 = volCell[1];
	volCell2 = ( volCell[2] - volCell[1] );
	volCell3 = ( volCellT - volCell2 - volCell1 ) ;

	if (volCell2 <= 3.00){
		volCell2 = 0.00 ;
		volCell3 = 0.00 ;
	} else {
		qtCell = 2 ;

		if (volCell3 <= 3.00) {
			volCell3 = 0.00 ;
		} else {
			qtCell = 3 ;
		}

	}
}


void sendSerialMessage(){

	//String serialMessage[] = {"<", qtCell , "," ,volCell1 ","};
	Serial.print("<");
	Serial.print(qtCell);
	Serial.print(",");
	Serial.print(volCell1);
	Serial.print(",");
	Serial.print(volCell2);
	Serial.print(",");
	Serial.print(volCell3);
	Serial.print(",");
	Serial.print(volCellT);
	Serial.println(">");

}

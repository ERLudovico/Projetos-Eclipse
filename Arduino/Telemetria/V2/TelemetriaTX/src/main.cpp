#include <Arduino.h>

#define _DELAY_ 250000
#define _NUMAMOSTRAS_ 10

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

static String CARAC_INICIO = "<" ;
static String CARAC_FIM    = ">" ;
static String CARAC_SEPARA = "," ;

unsigned long timet;
boolean enterFunction = true;
unsigned long previousTime;

/*
 * Declarando funcoes
 */
void sendSerialMessage();
void getVolCellPin();
void setTimet();

void setup() {
	Serial.begin(9600);
}

void loop() {
	timet = micros();
	if (enterFunction == true){
		previousTime= timet;
		getVolCellPin();
		sendSerialMessage();
	}
	setTimet();

}

void setTimet(){
  if (timet - previousTime < _DELAY_){
	enterFunction= false;
  }  else {
	enterFunction= true;
  }
}

void getVolCellPin(){
	qtCell = 1 ;
	for (int c=1; c<=3 ;c++){
		float tempVolt = 0.00 ;
		for (int i=0; i<_NUMAMOSTRAS_; i++){
			tempVolt += (analogRead(pinCell[c]) * (5.015 / 1023.0) );
		}
		tempVolt = tempVolt / _NUMAMOSTRAS_ ;
		volCell[c] = tempVolt * volCellOffset[c] ;
	}

	volCellT = volCell[3] ;
	volCell1 = volCell[1];
	volCell2 = ( volCell[2] - volCell[1] );
	volCell3 = ( volCellT - volCell2 - volCell1 ) ;

	if ( volCell1 <= 3.00){
		qtCell = 0 ;
		volCell1 = 0.00 ;
		volCell2 = 0.00 ;
		volCell3 = 0.00 ;
	} else if (volCell2 <= 3.00){
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

	Serial.print(CARAC_INICIO);
	Serial.print(qtCell);
	Serial.print(CARAC_SEPARA);
	Serial.print(volCell1);
	Serial.print(CARAC_SEPARA);
	Serial.print(volCell2);
	Serial.print(CARAC_SEPARA);
	Serial.print(volCell3);
	Serial.print(CARAC_SEPARA);
	Serial.print(volCellT);
	Serial.println(CARAC_FIM);

}

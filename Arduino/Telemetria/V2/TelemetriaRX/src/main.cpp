#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define _DELAY_ 250000
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void checkTimet();
void blickLED(int);
void parseData();
void debugParsedData();
void displayOLEDData();
void validaComunicacao();
void recvWithStartEndMarkers();
void generateMockValues();

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];

// variables to hold the parsed data
//char messageFromTX[numChars] = {0};

boolean newData = false;
boolean ledRXLOW = true ;

int qtCell = 0 ;
float voltCell[]    = { 0.00, 0.00, 0.00 ,  0.00 };
float voltPackMin[] = { 0.00, 3.80, 7.60 , 11.40 };
float voltPackMed[] = { 0.00, 4.00, 8.00 , 12.00 };
float voltCellT = 0.00;

static char CARAC_INICIO = '<' ;
static char CARAC_FIM    = '>' ;

float seno;
int frequencia;

boolean blinkON = false ;

int comunFailedCount = 0 ;
unsigned long timet;
unsigned long previousTime;

boolean enterFunction = true;
// Variaveis debug
//boolean debugOLED = false;

//============

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(9,OUTPUT);

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();
}

//============

void loop() {
	//timet = micros();
	//previousTime = timet;
	//validaComunicacao();
    //if (debugOLED) {
    //	generateMockValues();
    //} else {
	recvWithStartEndMarkers();
	if (newData == true) {
		blickLED(10);
		strcpy(tempChars, receivedChars);
		parseData();
		debugParsedData();
		newData = false;
	}
    //}
	displayOLEDData();
    if ( enterFunction ){
    	previousTime = timet;
    	if (blinkON) {
    		blinkON = false ;
    	} else {
       		blinkON = true ;
    	}
    }
    checkTimet();

}

//============

//void generateMockValues(){
//
//}

void checkTimet(){

  if (timet - previousTime < _DELAY_){
	  enterFunction = false;
  }  else {
	  enterFunction = true;
  }
}

void displayOLEDData(){
	  display.clearDisplay();

	  display.setTextSize(1);
	  display.setTextColor(WHITE);
	  display.setCursor(0,0);
	  display.print("  ");

	  for (int c=1; c<=qtCell;c++){

		  if ( voltCell[c] <= voltPackMin[1]){

			  display.setTextColor(BLACK, WHITE);
			  display.print(voltCell[c]);

		  } else if ( voltCell[c] <= voltPackMed[1]){

			  if (blinkON) {
				  display.setTextColor(BLACK, WHITE);
			  } else {
				  display.setTextColor(WHITE);
			  }
			  display.print(voltCell[c]);
		  } else {
			  display.setTextColor(WHITE);
			  display.print(voltCell[c]);
		  }

		  display.setTextColor(WHITE);
		  if ( c <= ( qtCell - 1) ){ display.print(" | ");}
	  }

	  display.drawLine(0, 8, display.width(), 8, WHITE);

	  display.setTextSize(3);
	  display.setTextColor(WHITE);
	  display.setCursor(0,10);
	  display.print(" ");

	  if ( voltCellT <= voltPackMin[qtCell]){

		  display.setTextColor(BLACK, WHITE);
		  display.print(voltCellT);

	  } else if ( voltCellT <= voltPackMed[qtCell]){
		  if (blinkON) {
			  display.setTextColor(BLACK, WHITE);
		  } else {
			  display.setTextColor(WHITE);
		  }
		  display.print(voltCellT);
	  } else {
		  display.setTextColor(WHITE);
		  display.print(voltCellT);
	  }

	  //display.print(voltCellT);

	  display.display();

}

void validaComunicacao(){
//	if (comunFailedCount > 1000) {
//		Serial.print(comunFailedCount);
//		tone(9,400);
//		delay(500);
//		noTone(9);

//		for(int x=0;x<180;x++){
//		  //converte graus para radiando e depois obtém o valor do seno
//		  seno=(sin(x*3.1416/180));
//		  //gera uma frequência a partir do valor do seno
//		  frequencia = 2000+(int(seno*1000));
//		  tone(9,frequencia);
//		  delay(2);
//		}
//	}
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char rc;
    comunFailedCount++ ;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != CARAC_FIM) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
                comunFailedCount = 0 ;
            }
        } else if (rc == CARAC_INICIO) {
            recvInProgress = true;
        }
    }
}

void blickLED(int _TIME_){

	digitalWrite(LED_BUILTIN, HIGH);
	delay(_TIME_);
	digitalWrite(LED_BUILTIN, LOW);

}

//============

void parseData() {      // split the data into its parts

    char * strtokIndx; // this is used by strtok() as an index

    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    qtCell = atoi(strtokIndx); // copy it to messageFromPC

    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    voltCell[1] = atof(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    voltCell[2] = atof(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    voltCell[3] = atof(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    voltCellT = atof(strtokIndx);     // convert this part to an integer

/*
    strtokIndx = strtok(tempChars,",");      // get the first part - the string
    strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC

    strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
    integerFromPC = atoi(strtokIndx);     // convert this part to an integer

    strtokIndx = strtok(NULL, ",");
    floatFromPC = atof(strtokIndx);     // convert this part to a float
*/

}

//============

void debugParsedData() {
	Serial.print("RX");
    Serial.print(CARAC_INICIO);
    Serial.print(",");
    Serial.print(qtCell);
    Serial.print(",");
    Serial.print(voltCell[1]);
    Serial.print(",");
    Serial.print(voltCell[2]);
    Serial.print(",");
    Serial.print(voltCell[3]);
    Serial.print(",");
    Serial.print(voltCellT);
    Serial.println(CARAC_FIM);
}

#include <Arduino.h>


void blickLED(int);
void parseData();
void debugParsedData();
void validaComunicacao();
void recvWithStartEndMarkers();

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];

// variables to hold the parsed data
//char messageFromTX[numChars] = {0};

boolean newData = false;
boolean ledRXLOW = true ;

int qtCell = 0 ;
float voltCell[] = { 0.00, 0.00, 0.00 ,0.00};
float voltCellT = 0.00;

static char CARAC_INICIO = '<' ;
static char CARAC_FIM    = '>' ;



float seno;
int frequencia;



int comunFailedCount = 0 ;

// Variaves do timet
unsigned long timet;
boolean enterFunction = true;
unsigned long previousTime;

//============

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(9,OUTPUT);
}

//============

void loop() {
	timet = millis();
	validaComunicacao();
    recvWithStartEndMarkers();
    //blickLED();
    if (newData == true) {
        blickLED(10);
        strcpy(tempChars, receivedChars);
        parseData();
        debugParsedData();
        newData = false;
    }

}

//============

void validaComunicacao(){
	if (comunFailedCount > 1000) {
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
	}
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

int finalTime = 0;
int agora = 0 ;

void blickLED(int _TIME_){

//	if (ledRXLOW == true){
//		digitalWrite(LED_BUILTIN, HIGH);
//		ledRXLOW = false;
//		finalTime = 5000 + millis();
//	} else {
//		agora = millis();
//		if ( agora >= finalTime){
//			digitalWrite(LED_BUILTIN, LOW);
//			ledRXLOW = true;
//		}
//	}
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
	Serial.print("RX ");
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

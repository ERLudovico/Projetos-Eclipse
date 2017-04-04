#include <SPI.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "LCD_Def.h"

/*
 * CONSTANTES PARA DEFINICAO
 * DOS PERIFERICOS
 */

#define usaPcd8544    true

void setup() {

	  if (usaPcd8544){
	    /* Ajuste Vcc do Display*/
	    turnONDisplay(); // Energiza pino do Display
	    initDisplay();   // Envia comando de inicializacao ao Display
	  }

}

void loop() {
	//Exemplo
	display.clearDisplay();
	  //display.setRotation(1);  // rotate 90 degrees counter clockwise, can also use values of 2 and 3 to go further.
	  display.setTextSize(1);
	  display.setTextColor(BLACK);
	  display.setCursor(0,0);
	  display.println("Rotation");
	  display.setTextSize(1);
	  display.println("Eduardo Rafael Ludovico");
	  display.display();
}


#include <SPI.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

/*
 * Definicoes para uso do LCD
 */

#define P8544_RST  3 // RESET
#define P8544_CS   4 // Chip Select
#define P8544_DC   5 // Data / Command
#define P8544_DIN  6 // Data in
#define P8544_CLK  7 // Clock

/*
 * Pino de Alimentacao do DISPLAY
 */
#define vccDisplay  12

/****************
 * CONSTRUTOR
 ****************/

Adafruit_PCD8544 display = Adafruit_PCD8544(P8544_CLK, P8544_DIN, P8544_DC, P8544_CS, P8544_RST);

/*********************
 * FUNCOES AUXILIARES
 *********************/

/*Display*/
void turnONDisplay(); // Energiza pino do Display
void initDisplay();   // Envia comando de inicializacao ao Display
void turnOFFDisplay();
/*
 * Funcoes auxiliares do DISPLAY
 */

/* Liga o Display */
void turnONDisplay() {
    pinMode(vccDisplay, OUTPUT);
    digitalWrite(vccDisplay, LOW);
}

/* Desliga o Display */
void turnOFFDisplay() {
    digitalWrite(vccDisplay, HIGH);
}

/* Inicializa o Display */
void initDisplay() {
    display.begin();
    display.setContrast(20);
    display.clearDisplay();

}

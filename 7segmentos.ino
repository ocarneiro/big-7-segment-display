// Display de 7 segmentos usando a biblioteca NeoPixel
// Ver API: https://adafruit.github.io/Adafruit_NeoPixel/html/class_adafruit___neo_pixel.html
#include <Adafruit_NeoPixel.h>

// pino de dados dos NeoPixels
#define PIN        7

// Quantos NeoPixels estão conectados?
#define NUMPIXELS 7

// Instancia a biblioteca
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 250 // milissegundos entre loops

uint32_t cor;

uint32_t cores[] = {
  pixels.Color(255, 0, 0),
  pixels.Color(0, 255, 0),
  pixels.Color(0, 0, 255),
  pixels.Color(255, 255, 0),
  pixels.Color(0, 255, 255),
  pixels.Color(255, 0, 255),
  pixels.Color(255, 120, 120)
};


void setup() {
  pixels.begin(); // Inicializa a biblioteca
}

void loop() {

  // ----- desligado -----  
  pixels.clear();
  pixels.show();
  delay(1000);
  
  cor = pixels.Color(255, 255, 255);

  // ------ 1 --------
  // cor = pixels.Color(120, 120, 120);
  pixels.clear();
  pixels.setPixelColor(1, cor);
  pixels.setPixelColor(2, cor);
  pixels.show();
  delay(1000);
  
  // ------ 2 --------
  // cor = pixels.Color(120, 120, 120);
  pixels.clear();
  pixels.setPixelColor(0, cor);
  pixels.setPixelColor(1, cor);
  pixels.setPixelColor(3, cor);
  pixels.setPixelColor(4, cor);
  pixels.setPixelColor(6, cor);
  pixels.show();
  delay(1000);

  // ------ 3 --------
  // cor = pixels.Color(120, 120, 120);
  pixels.clear();
  pixels.setPixelColor(0, cor);
  pixels.setPixelColor(1, cor);
  pixels.setPixelColor(2, cor);
  pixels.setPixelColor(3, cor);
  pixels.setPixelColor(6, cor);
  pixels.show();
  delay(1000);

  for(int i=0; i<7; i++) {
 
    cor = cores[i];
    pixels.clear();
    pixels.setPixelColor(0, cor);
    pixels.setPixelColor(1, cor);
    pixels.setPixelColor(2, cor);
    pixels.setPixelColor(3, cor);
    pixels.setPixelColor(4, cor);
    pixels.setPixelColor(5, cor);
    pixels.show();
    delay(DELAYVAL);
  }

  
  for(int i=0; i<7; i++) {
 
    cor = cores[i];
    pixels.clear();
    pixels.setPixelColor(0, cor);
    pixels.setPixelColor(1, cor);
    pixels.setPixelColor(2, cor);
    pixels.setPixelColor(3, cor);
    pixels.setPixelColor(4, cor);
    pixels.setPixelColor(5, cor);
    pixels.show();
    delay(DELAYVAL);
  }

  
  for(int i=0; i<7; i++) {
 
    cor = cores[i];
    pixels.clear();
    pixels.setPixelColor(0, cor);
    pixels.setPixelColor(1, cor);
    pixels.setPixelColor(2, cor);
    pixels.setPixelColor(3, cor);
    pixels.setPixelColor(4, cor);
    pixels.setPixelColor(5, cor);
    pixels.show();
    delay(DELAYVAL);
  }
}

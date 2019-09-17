// Simulação de display de status de bateria
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

uint32_t apagado = pixels.Color(0,0,0);

uint32_t cores[] = {
  pixels.Color(255, 0, 0),      // vermelho
  pixels.Color(0, 255, 0),      // verde
  pixels.Color(0, 0, 255),      // azul
  pixels.Color(255, 255, 0),    // amarelo
  pixels.Color(0, 255, 255),    // ciano
  pixels.Color(255, 0, 255),    // roxo
  pixels.Color(255, 190, 120)   // laranja
};


void setup() {
  pixels.begin(); // Inicializa a biblioteca
}

void loop() {

  // ----- O (cheio) -----  
  pixels.clear();
  cor = pixels.Color(0, 255, 0),      // verde
  pixels.setPixelColor(0, cor);
  pixels.setPixelColor(1, cor);
  pixels.setPixelColor(2, cor);
  pixels.setPixelColor(3, cor);
  pixels.setPixelColor(4, cor);
  pixels.setPixelColor(5, cor);
  pixels.show();
  delay(2000);
  
  cor = pixels.Color(255, 255, 255);

  // ------ 50% -U- --------
  cor = pixels.Color(255, 255, 0),    // amarelo
  pixels.clear();
  pixels.setPixelColor(1, cor);
  pixels.setPixelColor(2, cor);
  pixels.setPixelColor(3, cor);
  pixels.setPixelColor(4, cor);
  pixels.setPixelColor(5, cor);
  pixels.setPixelColor(6, cor);
  pixels.show();
  delay(2000);
  
  // ------ 10% U --------
  cor = pixels.Color(255, 0, 0),      // vermelho
  pixels.clear();
  pixels.setPixelColor(1, cor);
  pixels.setPixelColor(2, cor);
  pixels.setPixelColor(3, cor);
  pixels.setPixelColor(4, cor);
  pixels.setPixelColor(5, cor);
  pixels.show();
  delay(2000);

  // ------ 1% U_._._ --------
  cor = pixels.Color(255, 0, 0);      // vermelho
  pixels.clear();
  pixels.setPixelColor(1, cor);
  pixels.setPixelColor(2, cor);
  pixels.setPixelColor(4, cor);
  pixels.setPixelColor(5, cor);

  for(int i=0; i<6; i++) {
    pixels.setPixelColor(3, cor);
    pixels.show();
    delay(300);
    pixels.setPixelColor(3, apagado);
    pixels.show();
    delay(300);
  }

  cor = pixels.Color(255, 0, 0);      // vermelho
  for(int i=0; i<7; i++) {
 
    // ------ 0% U* --------
    pixels.clear();
    pixels.setPixelColor(1, cor);
    pixels.setPixelColor(2, cor);
    pixels.setPixelColor(3, cor);
    pixels.setPixelColor(4, cor);
    pixels.setPixelColor(5, cor);
    pixels.show();
    delay(150);
    pixels.clear();
    pixels.show();
    delay(150);
  }

    pixels.clear();
    pixels.show();
    delay(2000);

}

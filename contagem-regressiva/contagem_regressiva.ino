/* 
 *  Contagem regressiva
 *  Baseada no código de exemplo de Peter Hartmann
 *  para a biblioteca Seven Segment Pixel
 *  
 *  Criado em 2019 por Otávio Carneiro
 *  Este código é de domínio público
 */

#include <Adafruit_NeoPixel.h>
#include <Seven_Segment_Pixel.h>

// Pino conectado aos NeoPixels
#define PIN 6

// Quantos NeoPixels há no total?
#define NUMPIXELS 7

// Quantos dígitos há no display?
#define DIGITS 1

// Quantos pixels por segmento?
#define PIXPERSEG 1

// Quantos delimitadores há?
#define NUMDELIMS 0

// Quantos pixels por delimitador?
#define PIXPERDELIM 0

// Inicialização do display pela biblioteca Seven_Segment_Pixel
Seven_Segment_Pixel display1 =
    Seven_Segment_Pixel(DIGITS, PIXPERSEG, NUMDELIMS, PIXPERDELIM, NUMPIXELS,
                        PIN, NEO_RGB + NEO_KHZ800);

// Tamanho total da contagem
// Ao final da contagem, reinicia daqui
const int contagem_inicial = 9; // em segundos

int contagem = contagem_inicial;

void setup() {
  display1.begin(); // Inicializa os NeoPixels
}

void loop() {

  int minutos = contagem / 60;
  int dezenas_de_segundos = (contagem - minutos * 60) / 10;
  int unidades_de_segundos =
      contagem - (minutos * 60) - (dezenas_de_segundos * 10);

  if (DIGITS > 2) {
      display1.updateDigit(1, minutos, 255, 0, 0);
      display1.updateDigit(2, dezenas_de_segundos, 255, 0, 0);
      display1.updateDigit(3, unidades_de_segundos, 255, 0, 0);
  } else if (DIGITS > 1) {
      display1.updateDigit(1, dezenas_de_segundos, 255, 0, 0);
      display1.updateDigit(2, unidades_de_segundos, 255, 0, 0);
  } else {
      display1.updateDigit(1, unidades_de_segundos, 255, 0, 0);
  }

  if (NUMDELIMS > 0) {
    // Pisca delimitadores a cada segundo
    if (!(unidades_de_segundos % 2)) {
      //  segundos pares
      display1.updateDelimiter(1, 0, 0, 0);
    } else {
      //  segundos ímpares
      display1.updateDelimiter(1, 255, 0, 0);
    }
  }


  display1.show();

  delay(1000); // espera 1 segundo
  contagem--;  // reduz a contagem
  if (contagem == 0) {
    contagem = contagem_inicial;
  }
}

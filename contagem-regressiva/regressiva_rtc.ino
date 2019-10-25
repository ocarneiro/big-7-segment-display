/* 
 *  Contagem regressiva
 *  Baseada no código de exemplo de Peter Hartmann
 *  para a biblioteca Seven Segment Pixel
 *  
 *  Criado em 2019 por Otávio Carneiro
 *  Este código é de domínio público
 */

// Bibliotecas para NeoPixels em 7 segmentos 
#include <Adafruit_NeoPixel.h>
#include <Seven_Segment_Pixel.h>

// Bibliotecas para o RTC
#include <Wire.h>
#include "RTClib.h"

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

// valores de referencia
// 60 * 60 * 24
const long SEGUNDOS_EM_UM_DIA = 86400;

// 60 * 60
const long SEGUNDOS_EM_UMA_HORA = 3600;

const int SEGUNDOS_EM_UM_MINUTO = 60;


// Inicialização do display pela biblioteca Seven_Segment_Pixel
Seven_Segment_Pixel display1 =
    Seven_Segment_Pixel(DIGITS, PIXPERSEG, NUMDELIMS, PIXPERDELIM, NUMPIXELS,
                        PIN, NEO_RGB + NEO_KHZ800);

// Modo debug = imprime na porta serial
const boolean modo_debug = false;

long contagem;
long contagem_inicial;

RTC_DS1307 rtc; //Objeto rtc da classe DS1307

const DateTime data_alvo = DateTime(2019, 10, 24, 23, 07, 50);

void setup() {

  if (! rtc.begin()) {   //Se o RTC nao for inicializado, faz
    if (modo_debug) {
      Serial.println("RTC NAO INICIALIZADO");
    }
    while (1); //Trava o programa
  }
  
  DateTime agora = rtc.now();
  long segundos_alvo = data_alvo.secondstime();
  long segundos_atuais = agora.secondstime();

  contagem_inicial = segundos_alvo - segundos_atuais;
  contagem = contagem_inicial;

  display1.begin(); // Inicializa os NeoPixels
  if (modo_debug) {
    Serial.begin(9600); // Inicializa comunicação serial
  }
}

void loop() {

  uint8_t dias = contagem / SEGUNDOS_EM_UM_DIA;
  uint8_t dezenas_de_dias = dias / 10;
  uint8_t unidades_de_dias = dias % 10;

  long segundos_no_dia = contagem % SEGUNDOS_EM_UM_DIA;
  uint8_t horas = segundos_no_dia / SEGUNDOS_EM_UMA_HORA;
  uint8_t dezenas_de_horas = horas / 10;
  uint8_t unidades_de_horas = horas % 10;

  int segundos_na_hora = segundos_no_dia % SEGUNDOS_EM_UMA_HORA;
  uint8_t minutos = segundos_na_hora / SEGUNDOS_EM_UM_MINUTO;
  uint8_t dezenas_de_minutos = minutos / 10;
  uint8_t unidades_de_minutos = minutos % 10;
  
  uint8_t segundos = contagem % SEGUNDOS_EM_UM_MINUTO;
  uint8_t dezenas_de_segundos = segundos / 10;
  uint8_t unidades_de_segundos = segundos % 10;

  if (DIGITS > 7) {
      display1.updateDigit(1, dezenas_de_dias, 255, 0, 0);
      display1.updateDigit(2, unidades_de_dias, 255, 0, 0);
      display1.updateDigit(3, dezenas_de_horas, 255, 0, 0);
      display1.updateDigit(4, unidades_de_horas, 255, 0, 0);
      display1.updateDigit(5, dezenas_de_minutos, 255, 0, 0);
      display1.updateDigit(6, unidades_de_minutos, 255, 0, 0);
      display1.updateDigit(7, dezenas_de_segundos, 255, 0, 0);
      display1.updateDigit(8, unidades_de_segundos, 255, 0, 0);
  } else if (DIGITS >= 7) {
      display1.updateDigit(1, unidades_de_dias, 255, 0, 0);
      display1.updateDigit(2, dezenas_de_horas, 255, 0, 0);
      display1.updateDigit(3, unidades_de_horas, 255, 0, 0);
      display1.updateDigit(4, dezenas_de_minutos, 255, 0, 0);
      display1.updateDigit(5, unidades_de_minutos, 255, 0, 0);
      display1.updateDigit(6, dezenas_de_segundos, 255, 0, 0);
      display1.updateDigit(7, unidades_de_segundos, 255, 0, 0);
  } else if (DIGITS >= 6) {
      display1.updateDigit(1, dezenas_de_horas, 255, 0, 0);
      display1.updateDigit(2, unidades_de_horas, 255, 0, 0);
      display1.updateDigit(3, dezenas_de_minutos, 255, 0, 0);
      display1.updateDigit(4, unidades_de_minutos, 255, 0, 0);
      display1.updateDigit(5, dezenas_de_segundos, 255, 0, 0);
      display1.updateDigit(6, unidades_de_segundos, 255, 0, 0);
  } else if (DIGITS >= 3) {
      display1.updateDigit(1, unidades_de_minutos, 255, 0, 0);
      display1.updateDigit(2, dezenas_de_segundos, 255, 0, 0);
      display1.updateDigit(3, unidades_de_segundos, 255, 0, 0);
  } else if (DIGITS >= 2) {
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

  if (modo_debug) {
    // Serial.println(segundos_no_dia);
    String texto = "Faltam: " 
                 + String(dezenas_de_dias) + String(unidades_de_dias) + " dias, "
                 + String(dezenas_de_horas) + String(unidades_de_horas) + " horas, "
                 + String(dezenas_de_minutos) + String(unidades_de_minutos) + " minutos e "
                 + String(dezenas_de_segundos) + String(unidades_de_segundos) + " segundos.";
    Serial.println(texto);
  }

  delay(1000); // espera 1 segundo
  contagem--;  // reduz a contagem
  if (contagem < 0) {
    if (modo_debug) {
        Serial.print("Contagem final: ");
        Serial.println(contagem + 1);
     }
    while (1);
  }
}

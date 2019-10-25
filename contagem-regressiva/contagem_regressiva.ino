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
const boolean modo_debug = true;

long contagem;
long contagem_inicial;

void setup() {
  // Tamanho total da contagem
  // Ao final da contagem, reinicia daqui
  contagem_inicial = SEGUNDOS_EM_UM_DIA * 3; /* dias */
  contagem_inicial += SEGUNDOS_EM_UMA_HORA * 12; /* horas */
  contagem_inicial += SEGUNDOS_EM_UM_MINUTO * 29; /* minutos */
  contagem_inicial += 13; /* segundos */
  
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

  if (DIGITS > 2) {
      display1.updateDigit(1, unidades_de_minutos, 255, 0, 0);
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
  if (contagem == 0) {
    contagem = contagem_inicial;
  }
}

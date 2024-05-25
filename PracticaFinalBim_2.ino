#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

// Configuración del LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// Configuración del teclado matricial
const byte ROW_NUM = 4; 
const byte COL_NUM = 4; 
char keys[ROW_NUM][COL_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; 
byte pin_column[COL_NUM] = {5, 4, 3}; 
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COL_NUM);

// Configuración del servomotor
Servo servo; 

// Configuración de los LEDs
int leds[] = {10, 11, 12, 13}; 
int numLeds = 4;

// Configuración del decodificador
int decodificadorPins[] = {14, 15, 16, 17}; // Conecta los pines del decodificador a los pines de Arduino
int numPins = 4;

void setup() {
  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Victor Pantuj"); 
  lcd.setCursor(2, 1);
  lcd.print("Proyecto final"); 
  servo.attach(10); 
  for (int i = 0; i < numLeds; i++) {
    pinMode(leds[i], OUTPUT);
    }
  
   for (int i = 0; i < numPins; i++) {
    pinMode(decodificadorPins[i], OUTPUT);
  }
}

void loop() {

  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case '1':
        for (int i = 0; i <= 99; i++) {
          Serial.println(i);
          delay(1000);
        }
        break;
      case '2':
        for (int i = 99; i >= 0; i--) {
          Serial.println(i);
          delay(1000);
        }
        break;
      case '3':
        for (int j = 0; j < 3; j++) {
          for (int i = 0; i < numLeds; i++) {
            digitalWrite(leds[i], HIGH);
            delay(200);
            digitalWrite(leds[i], LOW);
          }
          for (int i = numLeds-1; i >= 0; i--) {
            digitalWrite(leds[i], HIGH);
            delay(200);
            digitalWrite(leds[i], LOW);
          }
        }
        for (int j = 0; j < 3; j++) {
          for (int i = 0; i < numLeds; i++) {
            digitalWrite(leds[i], HIGH);
          }
          delay(200);
          for (int i = 0; i < numLeds; i++) {
            digitalWrite(leds[i], LOW);
          }
          delay(200);
        }
        break;
      case '4':
        int secuencia[] = {8, 3, 8, 3}; // Secuencia de números a mostrar
        for (int i = 0; i < 4; i++) {
          mostrarNumero(secuencia[i]);
          delay(1000); // Espera un segundo antes de mostrar el siguiente número
        }
        break;
      case '5':
        for (int pos = 0; pos <= 180; pos += 1) {
          servo.write(pos);
          delay(15);
        }
        for (int pos = 180; pos >= 0; pos -= 1) {
          servo.write(pos);
          delay(15);
        }
        break;
    }
  }
}

void mostrarNumero(int numero) {
  for (int i = 0; i < numPins; i++) {
    digitalWrite(decodificadorPins[i], bitRead(numero, i));
  }
}
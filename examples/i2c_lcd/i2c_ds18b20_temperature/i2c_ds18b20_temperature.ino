/* 
  sensor temperatura
  
  o pino de dados deve estar ligado em 5v com resistot 4k7
  vermelho: vcc 5v
  preto: gnd
  dados: azul


  LCD
  SDA: A4
  SCL: A5
  VCC: 5v
  
  
  */

/*----- bibliotecas ds 18B20 -----*/
#include <OneWire.h>
#include <DallasTemperature.h>

/*----- bibliotecas LCD -----*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display


/*-----( Declare Constants )-----*/
#define T1 2 /*-(Connect to Pin 2 )-*/
#define T2 4 /*-(Connect to Pin 4 )-*/

/*-----( Declare objects )-----*/
/* Set up a oneWire instance to communicate with any OneWire device*/
OneWire ourWireOne(T1);
OneWire ourWireTwo(T2);

/* Tell Dallas Temperature Library to use oneWire Library */
DallasTemperature s1(&ourWireOne);
DallasTemperature s2(&ourWireTwo);

/*-----( Declare Variables )-----*/

int ajusteValorCelsius = 2;
float t1, t2;

void setup() {
  Serial.begin(9600);
  setupLCD();
  setupTemp();
}


void loop() {
  s1.requestTemperatures();
  t1 = s1.getTempCByIndex(0)-ajusteValorCelsius;

  s2.requestTemperatures();
  t2 = s2.getTempCByIndex(0)-ajusteValorCelsius;
  
  lcd.clear();
  lcd.print("T1: " + String(t1) + " C");
  lcd.setCursor(0, 1);
  lcd.print("T2: " + String(t2) + " C");
  delay(700);

}

void setupTemp() {
  lcd.clear();
  lcd.print("init temp...");
  s1.begin();
  s2.begin();
  lcd.setCursor(0, 1);
  lcd.print("OK!");
  delay(800);
}

void setupLCD() {
  lcd.init();
  lcd.backlight(); 
  lcd.print("init lcd...");
  delay(600);
  lcd.setCursor(0, 1);
  lcd.print("OK!");
  delay(600);
}

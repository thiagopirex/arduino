//DFRobot.com
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//pino SCL -> A5
//pino SDA -> A4

const int buttonPin = 2;
int buttonState = 0; 
int count;

void setup() {
  pinMode(buttonPin, INPUT);
  setupLCD(); 
  count = 0;
  //msg0();
  msgZ();
}

void loop() {
  //button();
  
}

void msgZ() {
  lcd.print("Bom dia amor,");
  lcd.setCursor(0, 1);
  lcd.print("bom treino!");
}

void setupLCD () {
  lcd.init();
  lcd.backlight();
}

void button() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    switch(count) {
      case 0:
        count++;       
        msg1();
        break;
      case 1:
        count++;       
        msg2();
        break;
      case 2:
        count++;       
        msg3();
        break;
      case 3:
        count=0;
        break;
    }
  }  
}

void msg0() {
  lcd.clear();
  lcd.print("Bom dia amor!");
  lcd.setCursor(0, 1);
  lcd.print("Aperte o botão");
}

void msg1() {
  lcd.clear();
  lcd.print("1");
}

void msg2() {
  lcd.clear();
  lcd.print("2");
}

void msg3() {
  lcd.clear();
  lcd.print("3");
}

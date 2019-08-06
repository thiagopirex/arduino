/* 
    

  vermelho: vcc 5v
  preto: gnd
  dados: azul


  LCD
  SDA: A4
  SCL: A5
  VCC: 5v
  
  
  */

/*----- bibliotecas LCD -----*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display


/* ---- bibliotecas relogio */
/* Relógio (RealTimeClock): DS1302
 *  
 *  CLK: D5 (digitla 5) - SCLK pin
 *  DAT: D3 (digital 3) - I/O pin
 *  RST: D2 (digital 2) - CE pin 
*/
#include <DS1302.h>
DS1302 rtc(2, 3, 4);//RealTimeClock






void setup() {
  Serial.begin(9600);
  setupLCD();

  //habilitar quando for necessário ajustar data/hora do relogio
  initClock();  

  
}


void loop() {


  
  lcd.clear();
  lcd.print(rtc.getTimeStr());
  lcd.setCursor(0, 1);
  lcd.print(rtc.getDateStr());
  delay(1000);


  
  
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

void initClock() {
  rtc.halt(false);
  rtc.writeProtect(false);
    //******************************* config de data/hora ****************************
  //rtc.setDOW(FRIDAY);        // Set Day-of-Week to FRIDAY
  //rtc.setTime(22, 37, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setTime(21, 59, 59);
  rtc.setDate(3, 3, 2019);   // Set the date to August 6th, 2010
  lcd.clear();
  lcd.print("Clock initializated!");
  delay(1500);
  
  lcd.clear();
  lcd.print(rtc.getDOWStr());
  delay(1500);
}

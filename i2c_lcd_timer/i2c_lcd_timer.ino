/*----- LCD -----*/
// i2c:     SDA pin   -> Arduino Analogic 4
//          SCL pin   -> Arduino Analogic 5
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display



/*----- RTC -----*/
// DS1302:  CE pin    -> Arduino Digital 2 (RST)
//          I/O pin   -> Arduino Digital 3 (DAT)
//          SCLK pin  -> Arduino Digital 4 (CLK)

#include <DS1302.h>
DS1302 rtc(2, 3, 4); //RealTimeClock


int horaInicio = 23;
int horaTermino = 23;
int horaAux;
int minInicio = 43;
int minTermino = 45;
int minAux;


String buffer;
boolean up = false;


void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  setupLCD();

  //enable this to ajust the first data and clock
  //configFirstTime();
}


void loop() {
  //lcd.clear();
  lcd.setCursor(8, 0);
  lcd.print(rtc.getTimeStr());

  lcd.setCursor(0, 0);
  if (up) {
    lcd.print("ON ");
  } else {
    lcd.print("OFF");
  }
  //lcd.setCursor(0, 1);
  //lcd.print(rtc.getDateStr());
  delay(990);

  turnOnOff();
}

void turnOnOff() {
  buffer = rtc.getTimeStr();
  horaAux = buffer.substring(0,2).toInt();//hora atual
  if (horaAux >= horaInicio && horaInicio <= horaTermino) { //21>=20 20<=22
    minAux = buffer.substring(3,5).toInt();//minuto atual
    if (minAux >= minInicio && minAux <= minTermino) {
      digitalWrite(13, HIGH);
      up = true;
    }
  }

  if (horaAux >= horaTermino ) { //se hora de termino do agendamento >= hora atual
    minAux = buffer.substring(3,5).toInt();//minuto atual
    if (minAux >= minTermino) { //se minuto de inicio do agendamento >= minuto atual
      digitalWrite(13, LOW);
      up = false;
    }
  }
}


void setupLCD() {
  lcd.init();
  lcd.backlight(); 
  lcd.print("init lcd...");
  delay(600);
  lcd.setCursor(0, 1);
  lcd.print("OK!");
  delay(600);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(horaInicio);
  lcd.print("h");
  lcd.print(minInicio);
  lcd.print(" --> ");
  lcd.print(horaTermino);
  lcd.print("h");
  lcd.print(minTermino);
  
}


void configFirstTime() {
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);

  // The following lines can be commented out to use the values already stored in the DS1302
  rtc.setDOW(FRIDAY);        // Set Day-of-Week to FRIDAY
  rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(6, 8, 2010);   // Set the date to August 6th, 2010
}

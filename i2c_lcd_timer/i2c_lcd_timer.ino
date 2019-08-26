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

/*----- RELE -----*/
//  Rele 1 pin   -> Arduino Digital 8
//  Rele 2 pin   -> Arduino Digital 9
int RELE_1 = 8;
int RELE_2 = 9;

int horaInicio = 15;
int horaTermino = 15;
int horaAux;
int minInicio = 40;
int minTermino = 50;
int minAux;


String buffer;
boolean up = false;


void setup() {
  pinMode(13, OUTPUT);
  pinMode(RELE_1, OUTPUT);
  pinMode(RELE_2, OUTPUT);
  Serial.begin(9600);
  digitalWrite(12, HIGH);
  setupLCD();

  digitalWrite(RELE_1, HIGH);
  digitalWrite(RELE_2, HIGH);

  
  //enable this to ajust the first data and clock
  //configFirstTime();
}


void loop() {
  //lcd.clear();
  lcd.setCursor(8, 0);
  lcd.print(rtc.getTimeStr());
  Serial.println(rtc.getTimeStr());

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
      digitalWrite(RELE_1, LOW);
      digitalWrite(RELE_2, LOW);
      up = true;
    }
  }

  if (horaAux >= horaTermino ) { //se hora de termino do agendamento >= hora atual
    minAux = buffer.substring(3,5).toInt();//minuto atual
    if (minAux >= minTermino) { //se minuto de inicio do agendamento >= minuto atual
      digitalWrite(13, LOW);
      digitalWrite(RELE_1, HIGH);
      digitalWrite(RELE_2, HIGH);
      up = false;
    }
  }
}


void setupLCD() {
  lcd.init();
  lcd.backlight(); 
  lcd.print("OK!");
  delay(600);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(horaInicio);
  lcd.print("h");
  if (minInicio < 10) {
    lcd.print("0");
  }
  lcd.print(minInicio);
  lcd.print(" --> ");
  lcd.print(horaTermino);
  lcd.print("h");
  if (minTermino < 10) {
    lcd.print("0");
  }
  lcd.print(minTermino);
}


void configFirstTime() {
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);

  // The following lines can be commented out to use the values already stored in the DS1302
  rtc.setDOW(MONDAY);        // Set Day-of-Week to FRIDAY
  rtc.setTime(15, 38, 20);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(26, 8, 2010);   // Set the date to August 6th, 2010
}

/*


  red: vcc 5v
  black: gnd
  blue: data


  LCD
  SDA: A4
  SCL: A5
  VCC: 5v


*/

/*----- libraries to use LCD -----*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


/*----- library to use dht11 sensor ----*/
#include "DHT.h"

// set the LCD address to 0x3F for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// set the pin to dht11 data
#define DHTPIN A1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


// Variables
const float MAX_HUMIDITY = 60;
const float MIN_HUMIDITY = 40;
const int RELE = 13;



void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("LCD OK!");
  pinMode(RELE, OUTPUT);
  dht.begin();
  delay(2000);
  lcd.clear();
}


void loop() {
  delay(5000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  // test if return is valid, else something is wrong
  if (isnan(t) || isnan(h)) {
    printValue("DHT failed");
  } else {
    printValues(h, t);
    controlRele(h);
  }
}

void printValue(String value) {
  Serial.println(value);
  lcd.clear();
  lcd.print(value);
}
void printValues(float humidity, float temperature) {
  Serial.print("humidity: ");
  Serial.print(humidity, 0);
  Serial.print("%   ");
  Serial.print("temperature: ");
  Serial.print(temperature, 0);
  Serial.println(" *C");

  lcd.clear();
  lcd.print("Temperatura: ");
  lcd.print(temperature, 0);
  lcd.print(" ºC");
  lcd.setCursor(0, 1);
  lcd.print("Umidade:");
  lcd.print(humidity, 0);
  lcd.print(" %");
}

void controlRele(float humidity) {
  if (humidity > MAX_HUMIDITY) {
    digitalWrite(RELE, LOW);
  }
  if (humidity < MIN_HUMIDITY) {
    digitalWrite(RELE, HIGH);
  }
}

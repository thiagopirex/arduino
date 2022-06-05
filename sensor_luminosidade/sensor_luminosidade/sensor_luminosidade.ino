/*----- libraries to use LCD -----*/
/* 
  LCD
  SDA: A4
  SCL: A5
  VCC: 5v
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// set the LCD address to 0x3F for a 16 chars and 4 line display
LiquidCrystal_I2C lcd(0x3F, 20, 4);


int pinorele = 12; //Pino ligado ao rele
int pinoled = 13; //Pino ligado ao rele
int pinoldr_A = A0; //Pino ligado ao sensor LRD - digital
int a0; //Variavel para guardar valor do sensor de luminosidade

int SENSOR = 950;


//https://www.filipeflop.com/blog/sensor-de-presenca-pir-detector-luminosidade/


void setup() {
  pinMode(pinorele, OUTPUT); //Define pino rele como saida 
  pinMode(pinoled, OUTPUT);  //Define pino led como saida
  pinMode(pinoldr_A, INPUT); //Define ldr (pino analógico A0) como entrada
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.print("LCD OK!");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("3...");
  delay(1000);
  lcd.setCursor(0, 2);
  lcd.print("2...");
  delay(1000);
  lcd.setCursor(0, 3);
  lcd.print("1...");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ligar?: ");
  lcd.setCursor(0, 1);
  lcd.print("Sensor: ");
}

void loop() {
  a0 = analogRead(pinoldr_A); //Le o valor do sensor LDR
  
  printSensor(a0);
  delay(500);
  if (turnOn(a0)) //Caso seja detectado ausência de luz, aciona o rele
  {
    digitalWrite(pinorele, LOW);
    digitalWrite(pinoled, HIGH);
    Serial.println("sem luz !!!");
  }
  else //Com luz, mantem rele desligado
  {
    digitalWrite(pinorele, HIGH);
    digitalWrite(pinoled, LOW);
    Serial.println("com luz");
  }
}

void printSensor(float value) {
  lcd.setCursor(11, 0);
  lcd.print("    ");
  lcd.print(String(turnOn(value)));
  lcd.setCursor(11, 1);
  lcd.print("    ");
  lcd.setCursor(11, 1);
  lcd.print(String(value));
}

boolean turnOn(int value) {
  return value >=  SENSOR; 
}

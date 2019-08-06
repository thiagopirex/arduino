/*
 * Fontes: 
 * 
 * 
 * 
 * https://www.filipeflop.com/blog/monitorando-temperatura-e-umidade-com-o-sensor-dht11/
 * https://eletricidadesemsegredosblog.wordpress.com/2017/09/19/programa-basico-para-teste-do-sensor-dht11-utilizando-monitor-serial/comment-page-1/
 * 
 */

#include "DHT.h"
 
#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

// ------------Sensor com 3 pinos
// Conecte o pino 1 do sensor ao pino de dados definido em seu Arduino
// Conecte o pino 2 do sensor (esquerda) ao +5V
// Conecte o pino 3 do sensor ao GND

// ------------Sensor com 4 pinos
// Conecte pinos 1 e 3 do sensor ao +5V
// Conecte o pino 2 ao pino de dados definido em seu Arduino
// Conecte o pino 4 do sensor ao GND

DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
}
 
void loop() {
  delay(2000);
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h))   {
    Serial.println("Failed to read from DHT");
  }   else  {
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
  }
}

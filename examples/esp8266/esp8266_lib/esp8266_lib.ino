// Programa : Teste modulo wireless ESP8266
// Autor : Arduino e Cia

//https://www.arduinoecia.com.br/2015/03/arduino-modulo-wireless-esp8266.html

// Carrega as bibliotecas ESP8266 e SoftwareSerial
#include "ESP8266.h"
#include "SoftwareSerial.h"
    
// Cria uma serial nas portas 2 (RX) e 3 (TX)
SoftwareSerial minhaSerial(2 , 3); 

// Define que o modulo ira utilizar a serial minhaSerial
ESP8266 wifi(minhaSerial);

// Configuracao ID e senha da rede Wireless
#define SSID        "Juliana"
#define PASSWORD    "giulia0310"


void setup()
{
    Serial.begin(9600);
}

void loop(void)
{
    Serial.print("Inicializando modulo\r\n");
    Serial.print("Versao do firmware: ");
    Serial.println(wifi.getVersion().c_str());
    // Define modo de operacao como STA (station)
    if (wifi.setOprToStation()) {
        Serial.print("Modo STA ok\r\n");
    } else {
        Serial.print("Erro ao definir modo STA !r\n");
    }
    
    // Conexao a rede especificada em SSID
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.print("Conectado com sucesso a rede wireless\r\n");
        Serial.print("IP: "); 
        delay(8000);      
        Serial.println(wifi.getLocalIP().c_str());
    } else {
        Serial.print("Erro ao conectar rede wireless !!!\r\n");
    }
    
    Serial.print("*** Fim ***\r\n");
    while(1){}
}

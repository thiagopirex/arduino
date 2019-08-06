// Programa: Web Server com modulo ESP8266
// Alteracoes e adaptacoes: FILIPEFLOP
 
#include <SoftwareSerial.h>
 
//ESP8266_TX->ARDUINO_RX (pino 2) 
//ESP8266_RX->ARDUINO_TX (pino 3)
SoftwareSerial esp8266(2, 3);
 
#define DEBUG true
String network = "Juliana";
String pwd = "giulia0310";

String response = "";
String closeCommand = "";
String mac = "5c:cf:7f:0b:c3:ea"; //Mac address of esp8266
boolean conectado = false;
int tentativas = 0;

//http://blog.filipeflop.com/wireless/esp8266-arduino-tutorial.html
 
void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  printMsg("Start setup\n");

  esp8266.begin(114200);

  conectar();

  printMsg("Finish setup");

  if (conectado) {
    Serial.print("\nConectado ao Access Point!\n");
    digitalWrite(13, HIGH);
  } else {
    Serial.print("\nNão foi possivel conectar ao Access Point!\n");
  }
    
}

void conectar() {
  sendData("AT+RST\r\n", 2000); // rst
  delay(2000);
  //Serial.println("Versao de firmware");
  //sendData("AT+GMR\r\n", 2000);
  //delay(2000);
  // Conecta a rede wireless
  sendData("AT+CWJAP=\"" + network + "\",\"" + pwd + "\"\r\n", 2000);
  Serial.print("Aguardando 8 segundos para se conectar ao Access Point\n");
  delay(8000);
  sendData("AT+CWMODE=1\r\n", 1000);
  delay(1000);
  // Mostra o endereco IP
  sendData("AT+CIFSR\r\n", 1000);
  delay(4000);
  // Configura para multiplas conexoes
  sendData("AT+CIPMUX=1\r\n", 1000);
  // Inicia o web server na porta 80
  sendData("AT+CIPSERVER=1,80\r\n", 1000);
}


void loop() {
  // Verifica se o ESP8266 está enviando dados
  if (esp8266.available()) {
    executar();  
  }
  if (!conectado) {
    blinkk();
    tentativas++;

    if (tentativas > 10) {
      printMsg("Realizando nova tentativa de conexão ao Access Point");
      tentativas = 0;
      conectar();
    }
  }

 
}

void executar() {
  if (esp8266.find("+IPD,"))
    {
      //delay(300);
      int connectionId = esp8266.read() - 48;

      String urlRequest = esp8266.readString();
      
      String resposta = "<head><meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\"></head><body>";
      String p1 = getValue(urlRequest, '/', 1);
      String p2 = getValue(urlRequest, '/', 2);

      if (p1 == "UP" || p1 == "DOWN") {
        if (p1 == "UP") {
           digitalWrite(13, HIGH);
           resposta += "13 to up!";
        } else {
           digitalWrite(13, LOW);
           resposta += "13 to down!";
        }
      } else {
        resposta += "request failed! Use /[UP/DOWN]/[DIGITAL PIN]/";
      }
      resposta += "</body>";

      

      
      String cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += resposta.length();
      cipSend += "\r\n";

      printMsg("#" + resposta + "#");
      
      sendData(cipSend, 1000);
      sendData(resposta, 1000);
 
      closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId; // append connection id
      closeCommand += "\r\n";
 
      sendData(closeCommand, 2000);
    }
}
 
String sendData(String command, const int timeout)
{
  // Envio dos comandos AT para o modulo
  String response = "";
  printMsg("SEND:" + command);
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      response += c;
    }
  }
  printMsg("\nRESPONSE:" + response);
  if (conectado == false && response.indexOf(mac) > 0) {
    conectado = true;
  }
  return response;
}

void blinkk() {
  digitalWrite(13, HIGH);
  delay(300);
  digitalWrite(13, LOW);
  delay(300);
}

void printMsg(String msg) {
  if (DEBUG) {
    Serial.print(msg);
  }
}

//https://stackoverflow.com/questions/29671455/how-to-split-a-string-using-a-specific-delimiter-in-arduino
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "Ambu";
const char* password = "LANCE001";
const int relay = 25;
String header; 
WiFiServer server(80);
String html ="<!DOCTYPE html> \
<html> \
<body> \
  <center><h1>Web Server</h1></center> \
</body> \
</html>";


void setup() {

  Serial.begin(115200);
  Serial.println("Connecting to Wifi");
  WiFi.softAP(ssid, password);
  server.begin();
  
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP); 

  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
}

void funct_relay () {
  digitalWrite(relay, LOW); // led is on
  delay(10000); 

  digitalWrite(relay, HIGH); //led is off
  delay(10000);
}

void loop() {
  String request = "";
  WiFiClient client=server.available(); // incoming client / user
  Serial.println("New Client");
  client.print(html);
  while(client.connected()){ 
      if (client.available()) {
        char c = client.read();
        header += c;
        if (c != '\r') {  // if you got anything else but a carriage return character,
          request += c;
        }

    }
  }
  Serial.print("UserID: ");
 
  int last = header.indexOf("HTTP/1.1");
  String numbers = header.substring(1, last - 1);
  Serial.print(numbers);
  request= "";
  header = "";
  funct_relay();
  client.stop();
  Serial.println("Client disconnected.");
  Serial.println("");
}

//relay part 
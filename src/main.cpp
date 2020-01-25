#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//0x0A, 0x2B, 0x49, 0x50, 0x44, 0x2C, 0x30, 0x2C, 0x34, 0x3A, 
byte relON1[] = {0xA0, 0x01, 0x01, 0xA2};  //Hex command to send to serial for open relay
byte relOFF1[] = {0xA0, 0x01, 0x00, 0xA1}; //Hex command to send to serial for close relay
byte relON2[] = {0xA0, 0x02, 0x01, 0xA3};  //Hex command to send to serial for open relay
byte relOFF2[] = {0xA0, 0x02, 0x00, 0xA2}; //Hex command to send to serial for close relay

int ledState = false;
unsigned long previousMillis = 0;
const long interval = 2000; //  2 seconds
ESP8266WebServer server(80);

//0 = idle
//1 = up
//2 = down

unsigned int state = 0;
unsigned long moveMillisLeft = 0;

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>WiFi LED on off demo: 1</h1><br>
Ciclk to turn <a href="ledOn">UP</a><br>
Ciclk to turn <a href="ledOff">DOWN</a><br>
</center>
 
</body>
</html>
)=====";

const char* ssid = "YOUR SSID HERE";
const char* password = "YOUR WIFI PW HERE";
 
void handleRoot() {
 Serial.println("You called root page");
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 
void handleLEDon() {
  moveMillisLeft = millis() + server.arg("time").toInt();
  state = 1;
  Serial.write(relON1, sizeof(relON1));
  Serial.flush();
  delay(100);
  server.send(200, "text/html", "LED is ON"); //Send ADC value only to client ajax request
}
 
void handleLEDoff() {
  moveMillisLeft = millis() + server.arg("time").toInt();
  state = 2;
  Serial.write(relON2, sizeof(relON2));
  Serial.flush();
  delay(100);
 server.send(200, "text/html", "LED is OFF"); //Send ADC value only to client ajax request
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/upp", handleLEDon); //as Per  <a href="ledOn">, Subroutine to be called
  server.on("/ner", handleLEDoff);
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
  unsigned long currentMillis = millis();
  if(currentMillis > moveMillisLeft && state != 0) {
    if (state == 1) {
      Serial.write(relOFF1, sizeof(relOFF1));
      Serial.flush();
      delay(100);
    } else if (state == 2) {
      Serial.write(relOFF2, sizeof(relOFF2));
      Serial.flush();
      delay(100);
    }
    state = 0;
  }
}
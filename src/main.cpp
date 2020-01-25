#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "lctech/relay.h"

int ledState = false;
unsigned long previousMillis = 0;
ESP8266WebServer server(80);

// 0 = idle, 1 = up, 2 = down
unsigned int state = 0;
unsigned long moveMillisLeft = 0;

const char* ssid = "";
const char* password = "";
 
void handleRoot() {
  server.send(200, "text/html", "Root view");
}
 
void handleUp() {
  moveMillisLeft = millis() + server.arg("time").toInt();
  state = 1;
  enableRelay(RELAY_ONE);
  server.send(200, "text/html", "Enable relay one");
}
 
void handleDown() {
  moveMillisLeft = millis() + server.arg("time").toInt();
  state = 2;
  enableRelay(RELAY_TWO);
  server.send(200, "text/html", "Enable relay two");
}

void setup(void){
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  
  //Todo move this to loop, if disconnected, it won't reconnect
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  server.on("/", handleRoot);
  server.on("/upp", handleUp);
  server.on("/ner", handleDown);
 
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  server.handleClient();
  unsigned long currentMillis = millis();
  if(currentMillis > moveMillisLeft && state != 0) {
    if (state == 1) {
      disableRelay(RELAY_ONE);
    } else if (state == 2) {
      disableRelay(RELAY_TWO);
    }
    state = 0;
  }
}
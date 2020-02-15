#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "lctech/relay.h"
#include "delay/delay.h"

ESP8266WebServer server(80);
Delay delayObj;

const char* ssid = "";
const char* password = "";
 
void handleRoot() {
  server.send(200, "text/html", "Root view");
}
 
void moveUp() {
  int timeToMove = server.arg("time").toInt();
  if (delayObj.start(millis(), timeToMove, []() { disableRelay(RELAY_ONE); })) {
    enableRelay(RELAY_ONE);
    server.send(200, "text/html", "Enable relay one success");
  } else {
    server.send(200, "text/html", "Enable relay one failed");
  }
}
 
void moveDown() {
  int timeToMove = server.arg("time").toInt();
  if (delayObj.start(millis(), timeToMove, []() { disableRelay(RELAY_TWO); })) {
    enableRelay(RELAY_TWO);
    server.send(200, "text/html", "Enable relay two success");
  } else {
    server.send(200, "text/html", "Enable relay two failed");
  }
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
  server.on("/up", moveUp);
  server.on("/down", moveDown);
 
  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
  delayObj.update(millis());
  server.handleClient();
}
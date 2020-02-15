#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "lctech/relay.h"
#include "delay/delay.h"
#include "storage/storage.h"
#include "html.hpp"

ESP8266WebServer server(80);
Delay delayObj;
Storage storage;

void handleRoot() {
  server.send(200, "text/html", generateHtml());
}

void handleSetup() {
  server.send(200, "text/html", generateSetup());
}

void handleConfig() {
  String ssid = server.arg("ssid");
  String pw = server.arg("pw");

  WifiConfig data;
  ssid.toCharArray(data.ssid, CONFIG_LENGTH);
  pw.toCharArray(data.pass, CONFIG_LENGTH);
  storage.saveWifiConfig(data);
  ESP.restart();
}
 
void moveUp() {
  int timeToMove = server.arg("time").toInt();
  if (delayObj.start(millis(), timeToMove, []() { disableRelay(RELAY_ONE); })) { enableRelay(RELAY_ONE);}
  server.send(200, "text/html", generateHtml());
}
 
void moveDown() {
  int timeToMove = server.arg("time").toInt();
  if (delayObj.start(millis(), timeToMove, []() { disableRelay(RELAY_TWO); })) {enableRelay(RELAY_TWO); }
  server.send(200, "text/html", generateHtml());
}

void setup(void){
  Serial.begin(115200);

  WifiConfig data = storage.loadWifiConfig();
  bool isWifiConfigured = data.ssid[0] == 0xFF;
  if(isWifiConfigured) {
    WiFi.softAP("IKEA-Bekant-IOT");
    Serial.println("AP IP address:");
    Serial.println(WiFi.softAPIP());
    server.on("/", handleSetup);
    server.on("/setup", handleConfig);
    
  } else {
    WiFi.begin(data.ssid, data.pass);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("IP address");
    Serial.println(WiFi.localIP());
    server.on("/", handleRoot);
    server.on("/up", moveUp);
    server.on("/down", moveDown);
  }

  server.begin();
}

void loop()
{
  delayObj.update(millis());
  server.handleClient();
}
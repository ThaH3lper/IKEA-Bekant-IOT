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

const char* root = "<!DOCTYPE html> <html> <head style=\"margin: 0;padding: 0;\"> <meta charset=\"UTF-8\"> <title>IKEA-Bekant-IOT</title><script src=\"https://code.jquery.com/jquery-1.11.3.js\"></script> <script> $(document).ready(function () { $(\"#success\").hide(); $(\"#failed\").hide(); }); </script> </head> <body style=\"margin: 0;padding: 0; text-align: center;\"> <div style=\"background-color: rgb(255, 174, 174);border-bottom: 5px solid rgb(167, 114, 114); position: absolute; top: 0; width: 100%;\" id=\"failed\"> <p style=\"font-size: 20px; display: inline-block;\"><b>Command failed:</b> already moving.</p> </div> <div style=\"background-color: rgb(197, 255, 174);border-bottom: 5px solid rgb(135, 175, 119); position: absolute; top: 0; width: 100%;\" id=\"success\"> <p style=\"font-size: 20px; display: inline-block;\"><b>Command success!</b></p> </div> <div style=\"width: 60%; margin: auto; padding-top: 60px\"> <h1 style=\"text-align: center;\">IKEA-Bekant-IOT</h1> <p style=\"margin-top: 32px;\">Move up:</p> <button onclick=\"window.location.href='/up?time=500'\">0.5s</button> <button onclick=\"window.location.href='/up?time=2000'\">2s</button> <button onclick=\"window.location.href='/up?time=5000'\">5s</button> <button onclick=\"window.location.href='/up?time=10000'\">10s</button> <button onclick=\"window.location.href='/up?time=15000'\">15s</button> <button onclick=\"window.location.href='/up?time=20000'\">20s</button> <button onclick=\"window.location.href='/up?time=25000'\">25s</button> <p style=\"margin-top: 32px;\">Move down:</p> <button onclick=\"window.location.href='/down?time=500'\">0.5s</button> <button onclick=\"window.location.href='/down?time=2000'\">2s</button> <button onclick=\"window.location.href='/down?time=5000'\">5s</button> <button onclick=\"window.location.href='/down?time=10000'\">10s</button> <button onclick=\"window.location.href='/down?time=15000'\">15s</button> <button onclick=\"window.location.href='/down?time=20000'\">20s</button> <button onclick=\"window.location.href='/down?time=25000'\">25s</button> <p style=\"margin-top: 32px; align-text: left;\">API</br>[ip]/up?time=[amount of time in ms]</br>[ip]/down?time=[amount of time in ms]</p> </div> </body> </html>";
const char* success = "<!DOCTYPE html> <html> <head style=\"margin: 0;padding: 0;\"> <meta charset=\"UTF-8\"> <title>IKEA-Bekant-IOT</title><script src=\"https://code.jquery.com/jquery-1.11.3.js\"></script> <script> $(document).ready(function () { $(\"#success\").delay(3000).fadeOut(700); $(\"#failed\").hide(); }); </script> </head> <body style=\"margin: 0;padding: 0; text-align: center;\"> <div style=\"background-color: rgb(255, 174, 174);border-bottom: 5px solid rgb(167, 114, 114); position: absolute; top: 0; width: 100%;\" id=\"failed\"> <p style=\"font-size: 20px; display: inline-block;\"><b>Command failed:</b> already moving.</p> </div> <div style=\"background-color: rgb(197, 255, 174);border-bottom: 5px solid rgb(135, 175, 119); position: absolute; top: 0; width: 100%;\" id=\"success\"> <p style=\"font-size: 20px; display: inline-block;\"><b>Command success!</b></p> </div> <div style=\"width: 60%; margin: auto; padding-top: 60px\"> <h1 style=\"text-align: center;\">IKEA-Bekant-IOT</h1> <p style=\"margin-top: 32px;\">Move up:</p> <button onclick=\"window.location.href='/up?time=500'\">0.5s</button> <button onclick=\"window.location.href='/up?time=2000'\">2s</button> <button onclick=\"window.location.href='/up?time=5000'\">5s</button> <button onclick=\"window.location.href='/up?time=10000'\">10s</button> <button onclick=\"window.location.href='/up?time=15000'\">15s</button> <button onclick=\"window.location.href='/up?time=20000'\">20s</button> <button onclick=\"window.location.href='/up?time=25000'\">25s</button> <p style=\"margin-top: 32px;\">Move down:</p> <button onclick=\"window.location.href='/down?time=500'\">0.5s</button> <button onclick=\"window.location.href='/down?time=2000'\">2s</button> <button onclick=\"window.location.href='/down?time=5000'\">5s</button> <button onclick=\"window.location.href='/down?time=10000'\">10s</button> <button onclick=\"window.location.href='/down?time=15000'\">15s</button> <button onclick=\"window.location.href='/down?time=20000'\">20s</button> <button onclick=\"window.location.href='/down?time=25000'\">25s</button> <p style=\"margin-top: 32px; align-text: left;\">API</br>[ip]/up?time=[amount of time in ms]</br>[ip]/down?time=[amount of time in ms]</p> </div> </body> </html>";
const char* failed = "<!DOCTYPE html> <html> <head style=\"margin: 0;padding: 0;\"> <meta charset=\"UTF-8\"> <title>IKEA-Bekant-IOT</title><script src=\"https://code.jquery.com/jquery-1.11.3.js\"></script> <script> $(document).ready(function () { $(\"#failed\").delay(3000).fadeOut(700); $(\"#success\").hide(); }); </script> </head> <body style=\"margin: 0;padding: 0; text-align: center;\"> <div style=\"background-color: rgb(255, 174, 174);border-bottom: 5px solid rgb(167, 114, 114); position: absolute; top: 0; width: 100%;\" id=\"failed\"> <p style=\"font-size: 20px; display: inline-block;\"><b>Command failed:</b> already moving.</p> </div> <div style=\"background-color: rgb(197, 255, 174);border-bottom: 5px solid rgb(135, 175, 119); position: absolute; top: 0; width: 100%;\" id=\"success\"> <p style=\"font-size: 20px; display: inline-block;\"><b>Command success!</b></p> </div> <div style=\"width: 60%; margin: auto; padding-top: 60px\"> <h1 style=\"text-align: center;\">IKEA-Bekant-IOT</h1> <p style=\"margin-top: 32px;\">Move up:</p> <button onclick=\"window.location.href='/up?time=500'\">0.5s</button> <button onclick=\"window.location.href='/up?time=2000'\">2s</button> <button onclick=\"window.location.href='/up?time=5000'\">5s</button> <button onclick=\"window.location.href='/up?time=10000'\">10s</button> <button onclick=\"window.location.href='/up?time=15000'\">15s</button> <button onclick=\"window.location.href='/up?time=20000'\">20s</button> <button onclick=\"window.location.href='/up?time=25000'\">25s</button> <p style=\"margin-top: 32px;\">Move down:</p> <button onclick=\"window.location.href='/down?time=500'\">0.5s</button> <button onclick=\"window.location.href='/down?time=2000'\">2s</button> <button onclick=\"window.location.href='/down?time=5000'\">5s</button> <button onclick=\"window.location.href='/down?time=10000'\">10s</button> <button onclick=\"window.location.href='/down?time=15000'\">15s</button> <button onclick=\"window.location.href='/down?time=20000'\">20s</button> <button onclick=\"window.location.href='/down?time=25000'\">25s</button> <p style=\"margin-top: 32px; align-text: left;\">API</br>[ip]/up?time=[amount of time in ms]</br>[ip]/down?time=[amount of time in ms]</p> </div> </body> </html>";

void handleRoot() {
  server.send(200, "text/html", root);
}
 
void moveUp() {
  int timeToMove = server.arg("time").toInt();
  if (delayObj.start(millis(), timeToMove, []() { disableRelay(RELAY_ONE); })) {
    enableRelay(RELAY_ONE);
    server.send(200, "text/html", success);
  } else {
    server.send(200, "text/html", failed);
  }
}
 
void moveDown() {
  int timeToMove = server.arg("time").toInt();
  if (delayObj.start(millis(), timeToMove, []() { disableRelay(RELAY_TWO); })) {
    enableRelay(RELAY_TWO);
    server.send(200, "text/html", success);
  } else {
    server.send(200, "text/html", failed);
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
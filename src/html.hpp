#include "Arduino.h"

const char* generateHtml() {
   const char* root = "<!DOCTYPE html>\
        <html>\
        <head style=\"margin: 0;padding: 0;\">\
            <meta charset=\"UTF-8\">\
            <title>IKEA-Bekant-IOT</title>\
        </head>\
        <body style=\"margin: 0;padding: 0; text-align: center;\">\
            <div style=\"width: 60%; margin: auto; padding-top: 60px\">\
                <h1 style=\"text-align: center;\">IKEA-Bekant-IOT</h1>\
                <p style=\"margin-top: 32px;\">Move up:</p>\
                <button onclick=\"window.location.href='/up?time=500'\">0.5s</button>\
                <button onclick=\"window.location.href='/up?time=2000'\">2s</button>\
                <button onclick=\"window.location.href='/up?time=5000'\">5s</button>\
                <button onclick=\"window.location.href='/up?time=10000'\">10s</button>\
                <button onclick=\"window.location.href='/up?time=15000'\">15s</button>\
                <button onclick=\"window.location.href='/up?time=20000'\">20s</button>\
                <button onclick=\"window.location.href='/up?time=25000'\">25s</button>\
                <p style=\"margin-top: 32px;\">Move down:</p>\
                <button onclick=\"window.location.href='/down?time=500'\">0.5s</button>\
                <button onclick=\"window.location.href='/down?time=2000'\">2s</button>\
                <button onclick=\"window.location.href='/down?time=5000'\">5s</button>\
                <button onclick=\"window.location.href='/down?time=10000'\">10s</button>\
                <button onclick=\"window.location.href='/down?time=15000'\">15s</button>\
                <button onclick=\"window.location.href='/down?time=20000'\">20s</button>\
                <button onclick=\"window.location.href='/down?time=25000'\">25s</button>\
                <p style=\"margin-top: 32px; align-text: left;\">API</br>[ip]/up?time=[amount of time in ms]</br>[ip]/down?time=[amount of time in ms]</p>\
            </div>\
        </body>\
        </html>";

    return root;
}

const char* generateSetup() {
   const char* root = "<!DOCTYPE html>\
        <html>\
        <head style=\"margin: 0;padding: 0;\">\
            <meta charset=\"UTF-8\">\
            <title>IKEA-Bekant-IOT</title>\
        </head>\
        <body style=\"margin: 0;padding: 0; text-align: center;\">\
            <div style=\"width: 60%; margin: auto; padding-top: 60px;\">\
                <h1 style=\"text-align: center;\">IKEA-Bekant-IOT</h1>\
                <form style=\"display: inline-block; text-align: left;\"action=\"/setup\" method=\"get\">\
                <label for=\"fname\">SSID: </label>\
                <input style=\"width: 100%;\" type=\"text\" name=\"ssid\"><br><br>\
                <label for=\"lname\">Password: </label>\
                <input style=\"width: 100%;\" type=\"password\" name=\"pw\"><br><br>\
                <input style=\"width: 100%;\" type=\"submit\" value=\"Save\">\
                </form>\
            </div>\
        </body>\
        </html>";

    return root;
}
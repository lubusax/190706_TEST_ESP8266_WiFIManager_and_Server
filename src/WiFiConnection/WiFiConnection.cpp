#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library 

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic


void ensure_wifi_connection(void) {

    WiFiManager wm;

    // wm.resetSettings(); uncomment if you want to reset the storedWiFi settings

    wm.autoConnect();

    Serial.println("Connected to WiFi...");
}

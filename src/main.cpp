#include <Arduino.h>
//#include <string>

#include "WiFiConnection/WiFiConnection.h"
#include "MyServer/MyServer.h"

MyServer myserver(80);

void setup() {

  Serial.begin(115200);

  ensure_wifi_connection();
  
  myserver.KickOff();

}

void loop() {

  myserver.ServerListen();

}

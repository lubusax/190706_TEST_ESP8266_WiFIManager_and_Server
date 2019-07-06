#include <Arduino.h>

#include "WiFiConnection/WiFiConnection.h"
#include "MyServer/MyServer.h"

MyServer myserver(80); // create instance of the server class

void setup() {

  Serial.begin(115200);

  ensure_wifi_connection();
  
  myserver.KickOff(); // server begin and also create instance of a client class

}

void loop() {

  myserver.ServerListen(); // handle the server-client communication

}

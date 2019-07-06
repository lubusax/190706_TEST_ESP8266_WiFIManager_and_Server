#pragma once
#include <ESP8266WiFi.h>

class MyServer: public WiFiServer
{
public:
    MyServer(uint16_t m_port);
    WiFiClient m_client;
    String m_header;
    String m_output5State;
    String m_output4State;
    void ServerListen(void);
    void KickOff(void);
private:
};
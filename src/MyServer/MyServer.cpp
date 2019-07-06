#include <ESP8266WiFi.h>

#include "MyServer.h"

MyServer::MyServer(uint16_t m_port):
WiFiServer(m_port)
{}

void MyServer::KickOff(void)
{
  this->begin();
  WiFiClient m_client;
    
  m_header="";// Variable to store the HTTP request
    
  m_output5State = "off";
  m_output4State = "off";// Auxiliar variables to store the current output state

  Serial.println(""); // Print local IP address
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}


void MyServer::ServerListen (void)
{
  m_client = this->available();
  if (m_client) {                             // If a new m_client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the m_client
    while (m_client.connected()) {            // loop while the m_client's connected
      if (m_client.available()) {             // if there's bytes to read from the m_client,
        char c = m_client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        m_header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the m_client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP m_headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the m_client knows what's coming, then a blank line:
            m_client.println("HTTP/1.1 200 OK");
            m_client.println("Content-type:text/html");
            m_client.println("Connection: close");
            m_client.println();
            
            // turns the GPIOs on and off
            if (m_header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              m_output5State = "on";
              //digitalWrite(output5, HIGH);
            } else if (m_header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              m_output5State = "off";
              //digitalWrite(output5, LOW);
            } else if (m_header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              m_output4State = "on";
              //digitalWrite(output4, HIGH);
            } else if (m_header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
              m_output4State = "off";
              //digitalWrite(output4, LOW);
            }
            
            // Display the HTML web page
            m_client.println("<!DOCTYPE html><html>");
            m_client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            m_client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            m_client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            m_client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            m_client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            m_client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            m_client.println("<body><h1>ESP8266 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 5  
            m_client.println("<p>GPIO 5 - State " + m_output5State + "</p>");
            // If the m_output5State is off, it displays the ON button       
            if (m_output5State=="off") {
              m_client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              m_client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            m_client.println("<p>GPIO 4 - State " + m_output4State + "</p>");
            // If the m_output4State is off, it displays the ON button       
            if (m_output4State=="off") {
              m_client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              m_client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            m_client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            m_client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the m_header variable
    m_header = "";
    // Close the connection
    m_client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

}
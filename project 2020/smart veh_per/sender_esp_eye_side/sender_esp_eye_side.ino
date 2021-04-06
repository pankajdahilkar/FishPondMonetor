/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-client-server-wi-fi/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

// Import required libraries
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>

// Set your access point network credentials
const char* ssid = "EYE_BLINK";
const char* password = "123456789";


int data = 10;
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
String readTemp() {
  return String(data);
  //return String(1.8 * bme.readTemperature() + 32);
}


int Blink_sensor = 2;
void setup() {
  // Serial port for debugging purposes
  Serial.begin(9600);
  Serial.println();
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", readTemp().c_str());
  });

  pinMode(Blink_sensor, INPUT);
  server.begin();
}

void loop() {
  data = digitalRead(Blink_sensor);
  Serial.println(data);
  
}

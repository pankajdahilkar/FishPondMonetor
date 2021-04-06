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
#include <Adafruit_MLX90614.h>

#include <Adafruit_Sensor.h>

// Set your access point network credentials
const char* ssid = "Social_distance_cap";
const char* password = "123456789";

/*#include <SPI.h>
#define BME_SCK 18
#define BME_MISO 19
#define BME_MOSI 23
#define BME_CS 5*/

String data;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readTemp() {
  float temp = mlx.readObjectTempF();
 
  data = String(temp);
  return data;
  //return String(1.8 * bme.readTemperature() + 32);
}



void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println(); 
  // Setting the ESP as an access point
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTemp().c_str());
  });
 
 
  
 mlx.begin(); 
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  // Start server
  server.begin();
}
 
void loop(){
 
}

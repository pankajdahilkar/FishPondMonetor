/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-static-fixed-ip-address-arduino/
*********/

// Load Wi-Fi library
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// Replace with your network credentials
const char* ssid     = "Pankaj D";
const char* password = "pankaj4u24";

// Set web server port number to 80
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
int data;
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)

// Set your Static IP address
IPAddress local_IP(192, 168, 43, 184);
// Set your Gateway IP address
IPAddress gateway(192, 168, 43, 1);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional
const int trigPin = D5;
const int echoPin = D6;

long duration;
int distance;
void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", []() {
    page = "<h1>Sensor to Node MCU Web Server</h1><h3>Data:</h3> <h4>" + String(data) + "</h4>";
    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Web server started!");
}

void loop() {

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    // if the LED is off turn it on and vice-versa:
    data = Garbgae_level();
    //  if(data>100) data=0;
  }
  delay(500);
  server.handleClient();
}


int Garbgae_level() {
  // Clears the trigPin
  int level ;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor //full 3 empty 12
  Serial.println("Distance = "+ distance);
  level = distance;
  int  distance_actual = distance;
  level = 12 - distance_actual;
  int    percenatge_level = level * 10;
    Serial.println("level %= "+ percenatge_level);

  return percenatge_level;
}

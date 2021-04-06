#include "DHT.h"
#include <LiquidCrystal.h>

#define ON 1
#define OFF 0
#define DHTPIN 2
#define DHTTYPE DHT11
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int incomingByte;      // a variable to read incoming serial data into
unsigned long previousMillis = 0, previousMillis_D1 = 0, previousMillis_D2 = 0;  // will store last time LED was updated
int water_level = 0;
// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)
const long interval_Display = 2500;           // interval at which to blink (milliseconds)
int trigPin = A4;    // Trigger
int echoPin = A5;    // Echo
long duration, cm, inches;
const int Valve_1 = 9;
const int Valve_2 = 10;
const int Valve_3 = 11;
const int Pump = 12;

char V1_FLAG = OFF;
char V2_FLAG = OFF;
char V3_FLAG = OFF;
char PUMP_FLAG = OFF;
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Valve_1, OUTPUT);
  pinMode(Valve_2, OUTPUT);
  pinMode(Valve_3, OUTPUT);
  pinMode(Pump, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // set up the LCD's number of columns and rows:
  dht.begin();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("Irrigation");
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("SCADA VIEW");
  delay(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  water_level_check();
  check_valves();
  Display_valve();
  Update_sensors();
}

void Update_sensors()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_D2 >= 2000) {
    previousMillis_D2 = currentMillis;
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    lcd.clear();
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("Temp = ");
    lcd.print(t);
    lcd.print("*C");
    lcd.setCursor(0, 1);
    // Print a message to the LCD.
    lcd.print("Humidity:");
    lcd.print(h);
    lcd.print("%");
    Serial.print('T');
    Serial.println(t);
    Serial.print('H');
    Serial.println(h);
  }
}

void  Display_valve()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_D1 >= interval_Display) {
    // save the last time you blinked the LED
    previousMillis_D1 = currentMillis;
    lcd.clear();
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("V1:");
    if ( V1_FLAG == ON ) lcd.print("ON ");
    else  lcd.print("OFF");
    lcd.print(" V2:");
    if ( V2_FLAG == ON ) lcd.print("ON ");
    else  lcd.print("OFF");
    lcd.setCursor(0, 1);
    // Print a message to the LCD.
    lcd.print("V3:");
    if ( V3_FLAG == ON ) lcd.print("ON ");
    else  lcd.print("OFF");
    lcd.print(" PUMP");
    if ( PUMP_FLAG == ON ) lcd.print("ON ");
    else  lcd.print("OFF");
    lcd.print("SCADA VIEW");
  }
}

void  water_level_check()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    long dist = Get_Distance_ultrasonic();
    int Most = analogRead(A3);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Water L = ");
    lcd.print(dist);
    lcd.print("*cm");
    lcd.setCursor(0, 1);
    lcd.print("Soil Moisture :");
    lcd.print(Most / 10);
    lcd.print("%");
    water_level = water_level + 10;
    Serial.print('W');
    Serial.println(water_level);
     Serial.print('M');
    Serial.println(Most/10);
    if (water_level > 99) {
      water_level = 0;
      delay(2000);
    }
  }
}

void check_valves()
{
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    switch (incomingByte)
    {
      case '1': {
          digitalWrite(Valve_1, HIGH);
          V1_FLAG = ON;
        } break;
      case'2': {
          digitalWrite(Valve_1, LOW);
          V1_FLAG = OFF;
        } break;
      case '3': {
          digitalWrite(Valve_2, HIGH);
          V2_FLAG = ON;
        } break;
      case'4': {
          digitalWrite(Valve_2, LOW);
          V2_FLAG = OFF;
        } break;
      case '5': {
          digitalWrite(Valve_3, HIGH);
          V3_FLAG = ON;
        } break;
      case'6': {
          digitalWrite(Valve_3, LOW);
          V3_FLAG = OFF;
        } break;
      case '7': {
          digitalWrite(Pump, HIGH);
          PUMP_FLAG = ON;
        } break;
      case'8': {
          digitalWrite(Pump, LOW);
          PUMP_FLAG = OFF;
        } break;
      default : 0;
    }
  }
}

long Get_Distance_ultrasonic()
{
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  // Convert the time into a distance
  cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
  return cm;
}

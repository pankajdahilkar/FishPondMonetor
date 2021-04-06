
#include "DHT.h"
#include <LiquidCrystal.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11
#define MOISTURE_SENS A0
#define CO2_SENS A1

// digital pin 2 has a pushbutton attached to it. Give it a name:
int t_int, h_int, CO2, moisture;
int FAN_STATUS = 0;
// the setup routine runs once when you press reset:
DHT dht(DHTPIN, DHTTYPE);
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int Fan_relay = 9;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(Fan_relay, OUTPUT);
  dht.begin();
  lcd.begin(16, 2);
  //  lcd.backlight();
  // Print a message to the LCD.
  lcd.print("Smart Food");
  lcd.setCursor(0, 1);
  lcd.print("Process viewer");
  delay(3000);
}

// the loop routine runs over and over again forever:
void loop() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  t_int = t;
  h_int = h;
  lcd.setCursor(0, 0);
  lcd.print("Temp = ");
  lcd.print(t_int);
  lcd.print("*C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity = ");
  lcd.print(h_int);
  lcd.print("%");
  delay(1500);

  moisture = analogRead(MOISTURE_SENS);
  CO2 = analogRead(CO2_SENS);
  lcd.setCursor(0, 0);
  lcd.print("Moisture = ");
  lcd.print(moisture / 10);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("CO2 Val = ");
  lcd.print(CO2 / 10);
  lcd.print(" ");
  delay(1500);

  if (t_int > 30)
  {
    FAN_STATUS = 1;
    digitalWrite(Fan_relay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Temperature HIGH");
    lcd.setCursor(0, 1);
    lcd.print("FAN ON");
  } else {
    FAN_STATUS = 0;
    digitalWrite(Fan_relay, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Temperature OK");
    lcd.setCursor(0, 1);
    lcd.print("FAN OFF");
  }
  delay(1500);
  Serial.print('A');
  Serial.println(FAN_STATUS);
  Serial.print('T');
  Serial.println(t_int);
  Serial.print('H');
  Serial.println(h_int);
  Serial.print('C');
  Serial.println(CO2 / 10);
  Serial.print('M');
  Serial.println(moisture / 10);
}

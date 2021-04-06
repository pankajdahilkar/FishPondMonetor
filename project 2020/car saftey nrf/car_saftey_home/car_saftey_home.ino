
#include <LiquidCrystal.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
 int inRange =0;
 int data_avail=0;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String Received_data;
void setup() {
  // set up the LCD's number of columns and rows:
  pinMode(A5,OUTPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  // Print a message to the LCD.
  lcd.print("home code");
  lcd.setCursor(0, 1);
  lcd.print("Vehicle saftey");
  delay(5000);
}

void loop() {

  //"WiFi Disconnected"

 if(Serial.available()>0) {
  Received_data = Serial.readString();
      inRange = Received_data.indexOf("WiFi Disconnected");
      data_avail = Received_data.indexOf("Data:");
 }
if(data_avail != -1)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vehicle safe");
    lcd.setCursor(0, 1);
    lcd.print(text);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Out of Range");
    lcd.setCursor(0, 1);
    lcd.print("Car moving ");
    digitalWrite(A5,HIGH);
    delay(1000);
    digitalWrite(A5,LOW);
    delay(1000);  
  }
}

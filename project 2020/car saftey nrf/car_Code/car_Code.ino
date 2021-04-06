
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <TinyGPS++.h>
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
static const int RXPin = 2, TXPin = A0;
static const uint32_t GPSBaud = 9600;
// The TinyGPS++ object
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
char flag = 0;
int buzzer = A5;
int sensor = A4;
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
String data, latitude, longitude;
void setup() {
  pinMode(buzzer, OUTPUT);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("vehicle");
  lcd.setCursor(0, 1);
  lcd.print("Security System");
  Serial.begin(9600);
  ss.begin(GPSBaud);
  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  Serial.println("AT+CLIP=1"); // activate the calletr id
  delay(1000);
  Serial.println("AT+DDET=1"); // activate the calletr id
  delay(1000);
  Serial.println("AT+CSQ"); // activate the calletr id
  delay(1000);
  delay(3000);
  // while (flag == 0)GpsRead();
}
void loop() {
  int sensor_val = analogRead(sensor);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor Reading");
  lcd.setCursor(0, 1);
  lcd.print(sensor_val);
  if (sensor_val > 600)
  {
    const char text[] = "vehicle safe";
    radio.write(&text, sizeof(text));
  }
  if (sensor_val < 400)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Alert Vehicle");
    lcd.setCursor(0, 1);
    lcd.print("Moving");
    lcd.print(sensor_val);
    //  const char text[] = "vehicle moved";
    //  radio.write(&text, sizeof(text));
    flag = 0;
    while (flag == 0)GpsRead();
    delay(20000);
  }
  //lcd.setCursor(0, 1);
  // lcd.print("From car");
  delay(2000);
  if (Serial.available() > 0)
  {
    String msg = Serial.readString();
    int isCall = msg.indexOf("+CLIP");
    if (isCall >= 0)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Call Value ");
      lcd.print(isCall);
      lcd.setCursor(0, 1);
      lcd.print("sending location");
      delay(3000);
      Serial.println("ATH");
      flag = 0;
      while (flag == 0)GpsRead();
    }
  }
  //
}


int GpsRead()
{
  while (ss.available() > 0)
  {
    if (gps.encode(ss.read()))
    {
      displayInfo();
    }

  }
}

int displayInfo()
{
  if (gps.location.isValid())
  {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LAT" + latitude);
    lcd.setCursor(0, 1);
    lcd.print("LANG" + longitude);
    delay(2000);
    sendsms();

    flag = 1;
  }
  else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("waiting ");
    lcd.setCursor(0, 1);
    lcd.print("for GPS");
    //  Serial.println("INVALID");
    delay(500);
  }

}

void sendsms()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sendig SMS");
  lcd.setCursor(0, 1);
  lcd.print("...>>>>>");
  delay(2000);
  Serial.println("AT+CMGF=1");    //Sets the Serial Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.print("AT+CMGS=");
  Serial.print('"');
  //Serial.print(valS);//  Serial.println("ATD+917798162899;");
  Serial.print("9156303112");
  Serial.print('"');
  Serial.println("\r"); // Replace x with mobile number
  delay(100);
  delay(1000);
  Serial.println("ALERT !! Car location "); // The SMS text you want to send
  Serial.print("www.google.com/maps/place/");
  Serial.print(gps.location.lat(), 8);
  Serial.print(',');
  Serial.println(gps.location.lng(), 8);
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
}

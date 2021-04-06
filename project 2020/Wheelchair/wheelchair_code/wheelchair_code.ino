#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillis1 = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)
const long interval_short = 200;           // interval at which to blink (milliseconds)

bool Buzzer_Flag = 0;
int ledState = LOW;             // ledState used to set the LED

int trigPin = A4;
int echoPin = A5;
int buzzer = A1;
const int Left_M1 = 9;
const int Left_M2 = 10;
const int Right_M1 = 11;
const int Right_M2 = 12;
int Distance = 0;
unsigned char blue_data;
SoftwareSerial mySerial(2, A3); // RX, TX

void setup()
{
  Serial.begin(9600);// set up serial communications with Right_M2Left_M100 baud rate
  mySerial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(Left_M1, OUTPUT);//motor 1a
  pinMode(Left_M2, OUTPUT);//motor 1b
  pinMode(Right_M1, OUTPUT);//motor 2a
  pinMode(Right_M2, OUTPUT);//motor 2b
  pinMode(buzzer, OUTPUT);
  digitalWrite(Left_M1, LOW);
  digitalWrite(Left_M2, LOW);
  digitalWrite(Right_M1, LOW);
  digitalWrite(Right_M2, LOW);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  sendsms( 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("__Welcome__");
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("Smart Wheelchair");
  delay(200);
}

void loop()
{
  Display();
  Display_alert();
  if (Serial.available() > 0)
  {
    blue_data = Serial.read();// get incoming byte from bluetooth
    if (blue_data == 'f' ) //forword
    {
      digitalWrite(Left_M1, HIGH);
      digitalWrite(Left_M2, LOW);
      digitalWrite(Right_M1, HIGH);
      digitalWrite(Right_M2, LOW);
      lcd.setCursor(0, 1);
      lcd.print("Forward");
    }
    else if (blue_data == 'd' ) //backword
    {
      digitalWrite(Left_M1, LOW);
      digitalWrite(Left_M2, HIGH);
      digitalWrite(Right_M1, LOW);
      digitalWrite(Right_M2, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("Reverse");
    }
    else  if (blue_data == 'l' ) //left turn
    {
      digitalWrite(Left_M1, LOW);
      digitalWrite(Left_M2, HIGH);
      digitalWrite(Right_M1, HIGH);
      digitalWrite(Right_M2, LOW);
      lcd.setCursor(0, 1);
      lcd.print("Left turn");
    }
    else  if (blue_data == 'r' ) // right turn
    {
      digitalWrite(Left_M1, HIGH);
      digitalWrite(Left_M2, LOW);
      digitalWrite(Right_M1, LOW);
      digitalWrite(Right_M2, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("Right Turn");
    }
    else if (blue_data == 's' ) // stop
    {
      digitalWrite(Left_M1, LOW);
      digitalWrite(Left_M2, LOW);
      digitalWrite(Right_M1, LOW);
      digitalWrite(Right_M2, LOW);
      lcd.setCursor(0, 1);
      lcd.print("Stop");
    }
    else if (blue_data == 's' ) // stop
    {
      digitalWrite(Left_M1, LOW);
      digitalWrite(Left_M2, LOW);
      digitalWrite(Right_M1, LOW);
      digitalWrite(Right_M2, LOW);
      lcd.setCursor(0, 1);
      lcd.print("Stop");
    } else if (blue_data == 'a' ) // stop
    {
      digitalWrite(Left_M1, LOW);
      digitalWrite(Left_M2, LOW);
      digitalWrite(Right_M1, LOW);
      digitalWrite(Right_M2, LOW);
      lcd.setCursor(0, 1);
      lcd.print("Stop");
      sendsms(1);
    } else if (blue_data == 'q' ) // stop
    {
      digitalWrite(Left_M1, LOW);
      digitalWrite(Left_M2, LOW);
      digitalWrite(Right_M1, LOW);
      digitalWrite(Right_M2, LOW);
      digitalWrite(buzzer, HIGH);
      lcd.setCursor(0, 1);
      lcd.print("HORN OK PLZ");
      delay(2000);
      digitalWrite(buzzer, LOW);
    }
  }
}
void Display()
{
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    Distance = CheckDistance();
    if(Distance < 20)Buzzer_Flag =1;
    else Buzzer_Flag =0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance = ");
    lcd.print(Distance);
  }
}

void Display_alert()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis1 >= interval) {
    // save the last time you blinked the LED
    previousMillis1 = currentMillis;
    if(Buzzer_Flag == 1){
 if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    // set the LED with the ledState of the variable:
        digitalWrite(buzzer, ledState);
    } else       digitalWrite(buzzer, LOW);
}
}
void Stop_chair()
{
  digitalWrite(Left_M1, LOW);
  digitalWrite(Left_M2, LOW);
  digitalWrite(Right_M1, LOW);
  digitalWrite(Right_M2, LOW);
}
int CheckDistance()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  return distance;
}


void sendsms(int state)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sendig SMS");
  lcd.setCursor(0, 1);
  lcd.print("...>>>>>");
  delay(2000);

  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.print("AT+CMGS=");
  mySerial.print('"');
  mySerial.print("9545861299");//  GSM.println("ATD+917798162899;");
  //GSM.print("9545861299");
  mySerial.print('"');
  mySerial.println("\r"); // Replace x with mobile number
  delay(100);
  delay(1000);
  if (state == 1)  {
    mySerial.print("I need Help ");

  }
  if (state == 2)  mySerial.println("System Initialize "); // The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
}

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define SLOT_1_SENS A0
#define SLOT_2_SENS A1
#define SLOT_3_SENS A2
#define SLOT_4_SENS A3
#define GATE_SENS   A4

const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo Gateservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int Slot_1_Val;
int Slot_2_Val;
int Slot_3_Val;
int Slot_4_Val;
int Gate_Val;
int total_slot_vacant = 0;
int s1 = 0;
int s2 = 0;
int s3 = 0;
int s4 = 0;


void setup()
{
  Serial.begin(9600);// set up serial communications with Right_M2Left_M100 baud rate
  // set up the LCD's number of columns and rows:
  Gateservo.attach(2);  // attaches the servo on pin 9 to the servo object

  pinMode(SLOT_1_SENS, INPUT);
  pinMode(SLOT_2_SENS, INPUT);
  pinMode(SLOT_3_SENS, INPUT);
  pinMode(SLOT_4_SENS, INPUT);
  pinMode(GATE_SENS, INPUT);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("Welcome");
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("Smart Parking system");
  delay(200);
}

void loop()
{
  Slot_1_Val = digitalRead(SLOT_1_SENS);
  Slot_2_Val = digitalRead(SLOT_2_SENS);
  Slot_3_Val = digitalRead(SLOT_3_SENS);
  Slot_4_Val = digitalRead(SLOT_4_SENS);
  Gate_Val = digitalRead(GATE_SENS);
  total_slot_vacant = 4 - (Slot_1_Val + Slot_2_Val + Slot_3_Val + Slot_4_Val);
  Serial.println(total_slot_vacant);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("P1=");
  if (Slot_1_Val) {
    lcd.print("FREE");
  } else {
    lcd.print("BUSY");
  }
  lcd.print(" P2=");
  if (Slot_2_Val) {
    lcd.print("FREE");
  } else {
    lcd.print("BUSY");
  }
  lcd.setCursor(0, 1);

  lcd.print("P3=");
  if (Slot_3_Val) {
    lcd.print("FREE");
  } else {
    lcd.print("BUSY");
  }
  lcd.print(" P4=");
  if (Slot_4_Val) {
    lcd.print("FREE");
  } else {
    lcd.print("BUSY");
  }
Update_webpage();


  delay(1200);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Gate:");
  lcd.print(Gate_Val);
  if (Gate_Val == LOW)
  {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Gate Open");
    Gateservo.write(89);              // tell servo to go to position in variable 'pos'
    delay(2000);
  } else {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Gate Close");
    Gateservo.write(0);              // tell servo to go to position in variable 'pos'
    delay(2000);
  }


}

void Update_webpage()
{
  if (Slot_1_Val) {
    Serial.println('a');
  } else {
    Serial.println('b');
  }  delay(200);

  if (Slot_2_Val) {
    Serial.println('c');
  } else {
    Serial.println('d');
  }  delay(200);


  if (Slot_3_Val) {
    Serial.println('e');
  } else {
    Serial.println('f');
  }  delay(200);

  if (Slot_4_Val) {
    Serial.println('g');
  } else {
    Serial.println('h');
  }  delay(200);
}

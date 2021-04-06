
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 10, 11, 12, 13, A0); // RS EN D4 D5 D6 DY7
int trigPin = A4;
int echoPin = A5;

void setup()
{
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  //  pinMode(buzzer, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Garbage Level");
  lcd.setCursor(0, 1);
  lcd.print("Monetoring");
  delay(3000);
}

void loop()
{
  int testDistance = CheckDistance(); /// get object distance using ping
  //  Serial.print(testDistance);
  //  Serial.println("cm");
  lcd.clear();
  int   dd = 12 - testDistance;
  int    percenatge_level = dd * 10;
  lcd.setCursor(0, 0);
  lcd.print("Garbage Level");
  lcd.setCursor(0, 1);
  lcd.print("d = ");
  lcd.print(percenatge_level);
  lcd.print(" % ");
  delay(1000);
Serial.println(percenatge_level);
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

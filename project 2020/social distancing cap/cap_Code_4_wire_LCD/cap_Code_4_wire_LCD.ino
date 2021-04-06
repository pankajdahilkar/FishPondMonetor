
#include <LCD_I2C.h>
LCD_I2C lcd(0x27); // Default address of most PCF8574 modules, change according
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
class Sweeper
{
    Servo servo;              // the servo
    int pos;              // current servo position
    int increment;        // increment to move for each interval
    int  updateInterval;      // interval between updates
    unsigned long lastUpdate; // last update of position

  public:
    Sweeper(int interval)
    {
      updateInterval = interval;
      increment = 1;
    }
    void Attach(int pin)
    {
      servo.attach(pin);
    }
    void Detach()
    {
      servo.detach();
    }
    void Update()
    {
      if ((millis() - lastUpdate) > updateInterval) // time to update
      {
        lastUpdate = millis();
        pos += increment;
        servo.write(pos);
        Serial.println(pos);
        if ((pos >= 180) || (pos <= 0)) // end of sweep
        {
          // reverse direction
          increment = -increment;
        }
      }
    }
};

/**************************** variables *****************************************/
Sweeper sweeper1(15);
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char flag = 0;
int trigPin = A3;
int echoPin = A2;
int buzzer = A1;
unsigned long previousMillis = 0;        // will store last time  was updated
// constants won't change:
const long interval = 1000;           // interval at which to repeat
/**************************** variables *****************************************/
float temperature = 0.00;

void setup() {
  pinMode(trigPin, OUTPUT);
  //  pinMode(buzzer, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  sweeper1.Attach(9);
  Serial.begin(9600);
  lcd.begin();
   lcd.backlight();
  // Print a message to the LCD.
  lcd.print("Corona cap");
  lcd.setCursor(0, 1);
  lcd.print("Social Distance");
  delay(3000);
  // while (flag == 0)GpsRead();
}
void loop() {
  int sensor_val = CheckDistance();
  sweeper1.Update();
  //  lcd.setCursor(0, 1);
  //  if (Serial.available() > 0)
  //  {
  //    String data = Serial.readStringUntil('\n');
  //    lcd.print(data);
  //  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("D =");
    // lcd.setCursor(0, 1);
    lcd.print(sensor_val);
    if (sensor_val < 20)
    { lcd.print(" ALERT!!!");
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);

    }
    lcd.setCursor(0, 1);
    if (Serial.available() > 0)
    {
      String data = Serial.readStringUntil('\n');
      temperature = data.toFloat();
                    lcd.print("Temp =");
      lcd.print(temperature);
      lcd.print("F");
      if (temperature > 99.0)
      {
        lcd.print(" ALERT!!!");
        digitalWrite(buzzer, HIGH);
        delay(200);
        digitalWrite(buzzer, LOW);

      }

    }
  }
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

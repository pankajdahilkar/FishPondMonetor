#include <LiquidCrystal.h>

//#include <LCD_I2C.h>
//LCD_I2C lcd(0x27); // Default address of most PCF8574 modules, change according


/**************************** variables *****************************************/
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char flag = 0;
int buzzer = A2;
int Engine = A1;
int Key_ignition = 9;
unsigned long previousMillis = 0;        // will store last time  was updated
// constants won't change:
const long interval = 1000;           // interval at which to repeat
/**************************** variables *****************************************/
float temperature = 0.00;
int Engine_flag = 0;
int alcohol_flag = 0;
int Eye_flag = 0;
int Alcohol_ir = A4;
int Alcohol_IR_state=0;
void setup() {

  pinMode(buzzer, OUTPUT);
  pinMode(Engine, OUTPUT);
  pinMode(Key_ignition, INPUT_PULLUP);
  pinMode(Alcohol_ir,INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  //  lcd.backlight();
  // Print a message to the LCD.
  lcd.print("Smart Vehicle");
  lcd.setCursor(0, 1);
  lcd.print("Operation");
  delay(3000);

}
void loop() {
  int sensor_val = analogRead(A5);
  int Ignition_state = digitalRead(Key_ignition);
  // save the last time you blinked the LED
  Alcohol_IR_state = digitalRead(Alcohol_ir);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("alco sens =");
  lcd.print(sensor_val);
  lcd.setCursor(0, 1);
  lcd.print("Key Status =");
  if (Ignition_state == LOW)
  { lcd.print("OFF");
    digitalWrite(Engine, LOW);
    Engine_flag = 0;
    alcohol_flag = 0;
    Eye_flag = 0;
  }
  else lcd.print(" ON");
  delay(1000);
  if (Ignition_state == HIGH)
  {
    if (sensor_val > 1000)
    {
      lcd.setCursor(0, 1);
      lcd.print(" ALERT!!! High Alocohol");
      digitalWrite(Engine, LOW);
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      alcohol_flag = 1;
      Engine_flag = 0;
    } else if(Alcohol_IR_state == LOW)
    {
      if ( alcohol_flag == 0)
      { Engine_flag = 1;
        lcd.setCursor(0, 1);
        lcd.print(" ENGINE ON");
        //  digitalWrite(Engine, HIGH);
      }
    }

    lcd.setCursor(0, 1);
    if (Serial.available() > 0)
    {
      String data = Serial.readStringUntil('\n');
      int  eye_state = data.toInt();
      if (eye_state == 1) {
        lcd.print("Eyes Open");
        if (Eye_flag == 0) Engine_flag = 1;
      } else {
        Eye_flag = 1;
        lcd.print("Eyes Close Engine OFF");
        Engine_flag = 0;
        digitalWrite(Engine, LOW );
      }
    }
    delay(1000);
    if (Engine_flag == 1 && Eye_flag == 0 && alcohol_flag == 0 )
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ALL GOOD");
      lcd.setCursor(0, 1);
      lcd.print(" ENGINE ON");
      digitalWrite(Engine, HIGH);
    } else
    {
      digitalWrite(Engine, LOW);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ALERT !!!!");
      lcd.setCursor(0, 1);
      lcd.print(" ENGINE OFF");
       digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
    }
    delay(1000);
  }
}

#include <LiquidCrystal.h>

#define ORGANIC 1
#define INORGANIC 2
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Inputs to the system
int Start_Button = 9;
int OBJECT_Button = 10;
int Time_Inc_Button = 11;
int Flap_detect = 12;
// State Variable of input

int Start_Button_State = HIGH;
int OBJECT_Button_State = HIGH;
int Time_Inc_Button_State = HIGH;
int Flap_detect_State = HIGH;
int type_object = ORGANIC;


//outputs from system
int Light_1 = A2;
int Light_2 = A3;

long Time_Now = 0;
long Time_elapsed = 0;
long Time_Set = 0;
long Time_counter = 0;

char Operation_Flag = false;
char Start_Flag = false;
char Light_Start_Flag = false;
char Organic_flag = false;
void check_Start_button();
void Start_Operation();
void Check_time_input();
void Display_Time_val();

void setup() {

  pinMode(Start_Button, INPUT);
  pinMode(OBJECT_Button, INPUT);
  pinMode(Time_Inc_Button, INPUT);
  pinMode(Flap_detect, INPUT);

  pinMode(Light_1, OUTPUT);
  pinMode(Light_2, OUTPUT);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("__Welcome__");
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("UV satization");
  delay(200);
}

void loop() {
  check_Object_button();
  if (Operation_Flag == false)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("__Welcome__");
    lcd.setCursor(0, 1);
    // Print a message to the LCD.
    lcd.print("Press Button");
    delay(100);
  }
  Check_time_input();
  check_Start_button();
  if (Start_Flag == true)
    Start_Operation();
}

void check_Start_button()
{
  Start_Button_State = digitalRead(Start_Button);
  if (Start_Button_State == LOW)
  {
    delay(50);
    Start_Button_State = digitalRead(Start_Button);
    if (Start_Button_State == LOW)
    {
      Start_Flag = true;
    }
  }
}

void check_Object_button()
{
  OBJECT_Button_State = digitalRead(OBJECT_Button);
  if (OBJECT_Button_State == LOW)
  {
    delay(50);
    OBJECT_Button_State = digitalRead(OBJECT_Button);
    if (OBJECT_Button_State == LOW)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      // Print a message to the LCD.
      lcd.print("Object Selected");
      lcd.setCursor(0, 1);
      // Print a message to the LCD.

      if (type_object == ORGANIC)
      {
        type_object = INORGANIC;
        Organic_flag = false;
        lcd.print("INORGANIC");
      } else {
        Organic_flag = true;
        type_object = ORGANIC;
        lcd.print("ORGANIC");
      }
    delay(2000);
    }
  }
}

void Start_Operation()
{
  Flap_detect_State = digitalRead(Flap_detect);
  if (Flap_detect_State == LOW)
  {
    delay(50);
    Flap_detect_State = digitalRead(Flap_detect);
    if (Start_Button_State == LOW)
    {
      Operate_light();
    }

  } else
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("Please Close");
    lcd.setCursor(0, 1);
    // Print a message to the LCD.
    lcd.print("Door ");
    digitalWrite(Light_1, LOW);
    digitalWrite(Light_2, LOW);
    Light_Start_Flag = false;
    delay(500);
  }
}
void Operate_light()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("Starting UV");
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("Sanitization  ");
  digitalWrite(Light_1, HIGH);
  if (Organic_flag == false)
  {
    digitalWrite(Light_2, HIGH);
  }
  Light_Start_Flag = true;
  delay(1500);
  Time_Now = millis();
  if (Time_counter == 0) Time_counter = 1;
  Time_Set = 1000 * 30 * Time_counter;
  while (((millis() - Time_Now) < Time_Set) && Light_Start_Flag == true)
  {
    Time_elapsed = millis() - Time_Now;
    lcd.clear();
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("Time Remain = ");
    lcd.print((Time_Set - Time_elapsed) / 1000);
    lcd.setCursor(0, 1);
    // Print a message to the LCD.
    lcd.print("UV light ON");
    delay(100);
    Flap_detect_State = digitalRead(Flap_detect);
    if (Flap_detect_State == HIGH)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      // Print a message to the LCD.
      lcd.print("ALERT>> DOOR OPEN");
      lcd.setCursor(0, 1);
      // Print a message to the LCD.
      lcd.print("UV LIGHT OFF");
      Organic_flag = false;
      digitalWrite(Light_1, LOW);
      digitalWrite(Light_2, LOW);
      Light_Start_Flag = false;
      Light_Start_Flag = false;
      Operation_Flag = false;
      Start_Flag = false;
      delay(500);
    }
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("OPERATION COMPLTE");
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("UV LIGHT OFF");
  digitalWrite(Light_1, LOW);
  digitalWrite(Light_2, LOW);
  Light_Start_Flag = false;
  Operation_Flag = false;
  Start_Flag = false;
  delay(500);
}

void Check_time_input()
{
  Time_Inc_Button_State = digitalRead(Time_Inc_Button);
  if (Time_Inc_Button_State == LOW)
  {
    delay(50);
    Time_Inc_Button_State = digitalRead(Time_Inc_Button);
    if (Time_Inc_Button_State == LOW)
    {
      Operation_Flag = true;
      Time_counter++;
      if (Time_counter > 4) Time_counter = 0;
      Display_Time_val();
    }
  }
}

void Display_Time_val()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("UV Satization ");
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("Time = ");
  lcd.print(Time_counter * 30);
  lcd.print("Sec");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("UV ");
  // Print a message to the LCD.
  lcd.print("Time = ");
  lcd.print(Time_counter * 30);
  lcd.print("Sec");
  lcd.setCursor(0, 1);
  lcd.print("Press START");
  delay(100);
}

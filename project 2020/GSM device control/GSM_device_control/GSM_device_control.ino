#include <LiquidCrystal.h>
#define ON 1
#define OFF 0
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int incomingByte;      // a variable to read incoming ////Serial data into
unsigned long previousMillis = 0, previousMillis_D1 = 0, previousMillis_D2 = 0;  // will store last time LED was updated
// constants won't change:
const long interval = 3000;           // interval at which to blink (milliseconds)
const long interval_Display = 3000;           // interval at which to blink (milliseconds)
const int Device_1 = 9;
const int Device_2 = 10;
const int Device_3 = 11;
const int Device_4 = 12;

char D1_FLAG = OFF;
char D2_FLAG = OFF;
char D3_FLAG = OFF;
char D4_FLAG = OFF;
String data;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Device_1, OUTPUT);
  pinMode(Device_2, OUTPUT);
  pinMode(Device_3, OUTPUT);
  pinMode(Device_4, OUTPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("Serial LOAD");
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("CONTROL SYSTEM");
  delay(200);
  initialize();
  RecieveMessage();
  //Serial.println("initialize");
 sendsms(1);
}

void loop() {

  Display_Device();
  operate_device();
}



void  Display_Device()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_D1 >= interval_Display) {
    // save the last time you blinked the LED
    previousMillis_D1 = currentMillis;
    lcd.clear();
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("D1:");
    if ( D1_FLAG == ON ) lcd.print("ON ");
    else  lcd.print("OFF");
    lcd.print(" D2:");
    if ( D2_FLAG == ON ) lcd.print("ON ");
    else  lcd.print("OFF");
    lcd.setCursor(0, 1);
    // Print a message to the LCD.
    lcd.print("D3:");
    if ( D3_FLAG == ON ) lcd.print("ON ");
    else  lcd.print("OFF");
    lcd.print(" D4");
    if ( D4_FLAG == ON ) lcd.print("ON ");
    else  lcd.print("OFF");
  }
}

void operate_device()
{
  if (Serial.available() > 0)
  {
    data = Serial.readString();
    // Serial.println(data);
    lcd.clear();
    lcd.setCursor(0, 0 );

    lcd.print(data.substring(0, 15));
    lcd.setCursor(0, 1 );
    lcd.print(data.substring(15));
    int Secrete_char = data.indexOf('*');
    delay(2000);
    char val_op = data.charAt(Secrete_char + 1);
    if (Secrete_char != -1)
    {
      switch (val_op)
      {
        case '1': {
            digitalWrite(Device_1, HIGH);
            D1_FLAG = ON;
          } break;
        case'2': {
            digitalWrite(Device_1, LOW);
            D1_FLAG = OFF;
          } break;
        case '3': {
            digitalWrite(Device_2, HIGH);
            D2_FLAG = ON;
          } break;
        case'4': {
            digitalWrite(Device_2, LOW);
            D2_FLAG = OFF;
          } break;
        case '5': {
            digitalWrite(Device_3, HIGH);
            D3_FLAG = ON;
          } break;
        case'6': {
            digitalWrite(Device_3, LOW);
            D3_FLAG = OFF;
          } break;
        case '7': {
            digitalWrite(Device_4, HIGH);
            D4_FLAG = ON;
          } break;
        case'8': {
            digitalWrite(Device_4, LOW);
            D4_FLAG = OFF;
          } break;
        default : 0;
      }
      sendsms(1);
    }
  }
}

void RecieveMessage()
{
  int ok_pos;

  Serial.println("AT+CMGF=1"); // AT Command to recieve a live SMS
  data = Serial.readString();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(data);
  ok_pos = data.indexOf("OK");
  if (ok_pos != -1)
  {
    lcd.setCursor(0, 1);
    lcd.print("Success");
  }
  delay(1000);
  ok_pos = -1;
  Serial.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  data = Serial.readString();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(data);
  ok_pos = data.indexOf("OK");
  if (ok_pos != -1)
  {
    lcd.setCursor(0, 1);
    lcd.print("Success");
  }
  delay(1000);
}


void initialize()
{

  int reg = 0, SIM = 0;
  String subdata;
  delay(4000);
  Serial.println("AT+CFUN?");
  delay(100);
  data = Serial.readString();
  //////Serial.println(data);
  subdata = data.substring(18, 20);
  //////Serial.println("subdata = " + subdata);
  while (SIM == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    Serial.println("AT+CPIN?");
    delay(100);
    data = Serial.readString();
    ////Serial.println(data);
    int simRegstat = data.indexOf("READY");
    lcd.print(data.substring(0, 15));
    lcd.setCursor(0, 1 );
    lcd.print(data.substring(15));
    ////Serial.println(" INSERT SIM");
    delay(1000);
    ////Serial.println("subdata = " + subdata);

    if (simRegstat != -1) {
      lcd.print("Sim Ready");
      ////Serial.println(" sim Ready");
      SIM = 1;
      delay(2000);
    }
    else {

      lcd.print("INSERT SIM");
      lcd.setCursor(0, 1 );
      lcd.print("RESTART System");
      ////Serial.println(" INSERT SIM");
      delay(1000);

    }
  }


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Registering.");
  while (reg != 1)
  {
    Serial.println("AT+CREG?");
    delay(100);
    data = Serial.readString();
    ////Serial.println(data);
    int simNetstat = data.indexOf("1");
    subdata = data.substring(20, 21);
    ////Serial.println("subdata = " + subdata);
    if (simNetstat != -1)
      reg = 1;
    lcd.setCursor(0, 0);
    lcd.print("Registering.");
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" SIM registered");
  delay(2000);
}



void sendsms(int state)
{

  Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.print("AT+CMGS=");
  Serial.print('"');
  Serial.print("9545861299");//  GSM.println("ATD+917798162899;");
  //GSM.print("9545861299");
  Serial.print('"');
  Serial.println("\r"); // Replace x with mobile number
  delay(100);
  delay(1000);
  if (state == 1)  {
    Serial.print("D1: ");
    if ( D1_FLAG == ON ) Serial.print("ON ");
    else  Serial.print("OFF");
    Serial.print("\n D2: ");
    if ( D2_FLAG == ON ) Serial.print("ON ");
    else  Serial.print("OFF");
//    Serial.setCursor(0, 1);
    // Print a message to the LCD.
    Serial.print("\n D3:");
    if ( D3_FLAG == ON ) Serial.print("ON ");
    else  Serial.print("OFF");
    Serial.print("\n D4");
    if ( D4_FLAG == ON ) Serial.print("ON ");
    else  Serial.print("OFF");
  }
  if (state == 2)  Serial.println("System Initialize "); // The SMS text you want to send
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
}

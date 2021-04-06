#include <LiquidCrystal.h>
#define ON 1
#define OFF 0
#define R_PHASE A5
#define Y_PHASE A4
#define B_PHASE A3

#define START_BUTTON 11
#define STOP_BUTTON  12

const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int incomingByte;      // a variable to read incoming ////Serial data into
unsigned long previousMillis = 0, previousMillis_D1 = 0, previousMillis_D2 = 0;  // will store last time LED was updated
// constants won't change:
const long interval = 1500;           // interval at which to blink (milliseconds)
const long interval_Display = 2000;           // interval at which to blink (milliseconds)
const int Device_1 = 9;
const int Device_2 = 10;

int R_phase_val;
int Y_phase_val;
int B_phase_val;
int Phase_fault = 0;
int Start_button_val;
int Stop_button_val;

char START_FLAG = 0;
char STOP_FLAG = 1;
char D1_FLAG = OFF;
char D2_FLAG = OFF;
char ERROR_FLAG = 0;
char Earth_Fault = 0;
char Phase2Phase_Fault = 0;

int fault_sms_flag = 0;
String data;
int display_counter = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Device_1, OUTPUT);
  pinMode(Device_2, OUTPUT);
  pinMode(START_BUTTON, INPUT);
  pinMode(STOP_BUTTON, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("3 Phase LOAD");
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print("CONTROL SYSTEM");
  delay(200);
  initialize();
  RecieveMessage();
  //Serial.println("initialize");
  //  sendsms(1);
}

void loop() {
  R_phase_val = analogRead(R_PHASE);
  Y_phase_val = analogRead(Y_PHASE);
  B_phase_val = analogRead(B_PHASE);
  if (R_phase_val < 300 || B_phase_val < 300 || Y_phase_val < 300)
    Phase_fault = 1;
  else Phase_fault = 0;
  Start_button_val = digitalRead(START_BUTTON);
  Stop_button_val =  digitalRead(STOP_BUTTON);
  if (Start_button_val == 0)
  {
    Earth_Fault = 1;
  } else  Earth_Fault = 0;

  if (Stop_button_val == 0)
  {
    Phase2Phase_Fault = 1;
  } else  Phase2Phase_Fault = 0;
  if (Phase_fault == 0 && Phase2Phase_Fault == 0 && Earth_Fault == 0)
  {
    if ( fault_sms_flag == 1)
      sendsms(4);

    fault_sms_flag = 0;

  }
  else {
    if ( fault_sms_flag == 0)
      sendsms(3);
    fault_sms_flag = 1;
  }
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_D1 >= interval_Display) {
    // save the last time you blinked the LED
    previousMillis_D1 = currentMillis;
    if (display_counter == 0) Display_Device();
    if (display_counter == 1) Display_Faults();
    if (display_counter == 2) {
      Display_Sensor();
      display_counter = 0;
    }
    display_counter++;
  }
  operate_device();
}



void  Display_Device()
{

  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print("Device :");
  if ( START_FLAG == ON ) {
    lcd.print("ON ");
    digitalWrite(Device_1, HIGH);
    digitalWrite(Device_2, HIGH);
  }
  if ( STOP_FLAG == ON )  {
    lcd.print("OFF");
    digitalWrite(Device_1, LOW);
    digitalWrite(Device_2, LOW);
  }
//  Serial.print(millis());
//  Serial.println(" in device  display ");

}

void  Display_Sensor()
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R:");
  if (R_phase_val < 300 )
    lcd.print("Fault");
  else lcd.print("OK");

  lcd.print(" Y:");
  if (Y_phase_val < 300 )
    lcd.print("Fault");
  else lcd.print("OK");

  lcd.setCursor(0, 1);
  lcd.print("B:");
  if (B_phase_val < 300 )
    lcd.print("Fault");
  else lcd.print("OK");

//  Serial.print(millis());
//  Serial.println(" in sensor  display ");

}

void  Display_Faults()
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EARTH:");
  if (Earth_Fault == 1 )
    lcd.print("Fault");
  else lcd.print("OK");
  lcd.setCursor(0, 1);
  lcd.print("Phase-Phase:");
  if (Phase2Phase_Fault == 1 )
    lcd.print("Fault");
  else lcd.print("OK");
//  Serial.print(millis());
//  Serial.println(" in Fault  display ");

}
void operate_device()
{
  if (Serial.available() > 0)
  {
    int data_len;
    data = Serial.readString();
    // Serial.println(data);
    data_len = data.length();
    lcd.clear();
    lcd.setCursor(0, 0 );
    lcd.print(data.substring(0, 15));
    lcd.setCursor(0, 1 );
    if (data_len > 32)
      lcd.print(data.substring(15, 31));
    else lcd.print(data.substring(15));
    if (data_len > 32)
    {
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0 );
      lcd.print(data.substring(31, 45));
      lcd.setCursor(0, 1 );
      lcd.print(data.substring(45));
    }
    int Secrete_char = data.indexOf('*');
    delay(2000);
    char val_op = data.charAt(Secrete_char + 1);
    if (Secrete_char != -1)
    {
      switch (val_op)
      {
        case '1': {
            if (Phase_fault == 0 && Phase2Phase_Fault == 0 && Earth_Fault == 0)
              START_FLAG = 1;
            STOP_FLAG = 0;
          } break;
        case'2': {
            START_FLAG = 0;
            STOP_FLAG = 1;
          } break;

        default : 0;
      }
      if (Phase_fault == 0 && Phase2Phase_Fault == 0 && Earth_Fault == 0) 1;
      // sendsms(1);
      //else  sendsms(3);
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
  Serial.print("9545861299");//
  Serial.print('"');
  Serial.println("\r"); // Replace x with mobile number
  delay(100);
  delay(1000);
  if (state == 1)  {
    Serial.print("Device: ");
    if ( START_FLAG == ON ) Serial.print("ON ");
    if ( STOP_FLAG == ON ) Serial.print("OFF ");
    //    Serial.setCursor(0, 1);
    // Print a message to the LCD.

  }
  if (state == 2)  Serial.println("System Initialize "); // The SMS text you want to send
  if (state == 4)  Serial.println("ALL FAULT clear \n System OK ... "); // The SMS text you want to send
  if (state == 3)
  {
    Serial.println("Fault occured"); // The SMS text you want to send
    if (Phase_fault == 1) Serial.println("PHASE NOT AVAILABLE");
    if (Phase2Phase_Fault == 1) Serial.println("PHASE TO PHASE FAULT OCCURED");
    if (Earth_Fault == 1) Serial.println("EARTH FAULT");
    Serial.println("System OFF");
  }
  delay(100);
  Serial.println((char)26);// ASCII code of CTRL+Z
}

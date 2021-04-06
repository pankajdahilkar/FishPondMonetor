#include <LCD_I2C.h>
#define ON_STATE 0
#define OFF_STATE 1
LCD_I2C lcd(0x27); // Default address of most PCF8574 modules, change according
// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// arrays to hold device address
DeviceAddress insideThermometer;

const long interval = 3000;           // interval at which to blink (milliseconds)
const long interval_idle_ON = 2000;           // interval at which to blink (milliseconds)

unsigned long previousMillis = 0,previousMillis_D = 0, previousMillis_D1 = 0, previousMillis_D2 = 0;  // will store last time LED was updated
unsigned long S1_Time_count = 0;
unsigned long S2_Time_count = 0;
unsigned long S3_Time_count = 0;
unsigned long S4_Time_count = 0;

const int Light_1 = A8;
const int Light_2 = A9;
const int Light_3 = A10;
const int Light_4 = A11;
const int Fan = A12;

const int sens_1 = A0;
const int sens_2 = A1;
const int sens_3 = A2;
const int sens_4 = A3;

int SensorState_1;
int SensorState_2;
int SensorState_3;
int SensorState_4;

bool Light_1_state = OFF_STATE;
bool Light_2_state = OFF_STATE;
bool Light_3_state = OFF_STATE;
bool Light_4_state = OFF_STATE;

void setup() {
  pinMode(Light_1, OUTPUT);
  pinMode(Light_2, OUTPUT);
  pinMode(Light_3, OUTPUT);
  pinMode(Light_4, OUTPUT);
  pinMode(Fan, OUTPUT);
  pinMode(sens_1, INPUT);
  pinMode(sens_2, INPUT);
  pinMode(sens_3, INPUT);
  pinMode(sens_4, INPUT);
  digitalWrite(Light_1, HIGH);
  digitalWrite(Light_2, HIGH);
  digitalWrite(Light_3, HIGH);
  digitalWrite(Light_4, HIGH);
  digitalWrite(Fan, HIGH);

  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
  // this stop the library(LCD_I2C) from calling Wire.begin()
  lcd.backlight();
  sensors.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  // Print a message to the LCD.
  lcd.print(F("Welcome"));
  lcd.setCursor(0, 1);
  // Print a message to the LCD.
  lcd.print(F("home automation"));
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0");
  Serial.print("Device 0 Address: ");
  printAddress(insideThermometer);
  Serial.println();

  // set the resolution to 9 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors.setResolution(insideThermometer, 9);

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(insideThermometer), DEC);
  Serial.println();
}

void loop() {
  Update_sensors();
  Update_display();
  fan_operation();
}
void Update_sensors()
{

  SensorState_1 = digitalRead(sens_1);
  SensorState_2 = digitalRead(sens_2);
  SensorState_3 = digitalRead(sens_3);
  SensorState_4 = digitalRead(sens_4);

  if (SensorState_1 == ON_STATE) Light_1_state = ON_STATE;
  if (SensorState_2 == ON_STATE) Light_2_state = ON_STATE;
  if (SensorState_3 == ON_STATE) Light_3_state = ON_STATE;
  if (SensorState_4 == ON_STATE) Light_4_state = ON_STATE;
  unsigned long currentMillis = millis();

  if ( SensorState_1 == ON_STATE)
  {
    S1_Time_count = currentMillis;
    digitalWrite(Light_1, LOW);
  }  if (SensorState_1 == OFF_STATE)
  {
    if (currentMillis - S1_Time_count >= interval_idle_ON) {
      Light_1_state = OFF_STATE;
      digitalWrite(Light_1, HIGH);
    }
  }

  if ( SensorState_2  == ON_STATE)
  {
    S2_Time_count = currentMillis;
    digitalWrite(Light_2, LOW);
  }  if (SensorState_2 == OFF_STATE)
  {
    if (currentMillis - S2_Time_count >= interval_idle_ON) {
      Light_2_state = OFF_STATE;
      digitalWrite(Light_2, HIGH);
    }
  }

  if ( SensorState_3 == ON_STATE)
  {
    S3_Time_count = currentMillis;
    digitalWrite(Light_3, LOW);
  }  if (SensorState_3 == OFF_STATE)
  {
    if (currentMillis - S3_Time_count >= interval_idle_ON) {
      Light_3_state = OFF_STATE;
      digitalWrite(Light_3, HIGH);
    }
  }

  if ( SensorState_4 == ON_STATE)
  {
    S4_Time_count = currentMillis;
    digitalWrite(Light_4, LOW);
  }  if (SensorState_4 == OFF_STATE)
  {
    if (currentMillis - S4_Time_count >= interval_idle_ON) {
      Light_4_state = OFF_STATE;
      digitalWrite(Light_4, HIGH);
    }
  }
}

void Update_display()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_D2 >= interval) {
    previousMillis_D2 = currentMillis;

    lcd.clear();
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print("L1:");
    if ( Light_1_state == ON_STATE ) lcd.print("ON ");
    else  lcd.print("OFF");
    lcd.print(" L2:");
    if ( Light_2_state == ON_STATE ) lcd.print("ON ");
    else  lcd.print("OFF");
    lcd.setCursor(0, 1);
    // Print a message to the LCD.
    lcd.print("L3:");
    if ( Light_3_state == ON_STATE ) lcd.print("ON ");
    else  lcd.print("OFF");
    lcd.print(" L4:");
    if ( Light_4_state == ON_STATE ) lcd.print("ON ");
    else  lcd.print("OFF");
  }
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
void fan_operation()
{

  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  // It responds almost immediately. Let's print out the data
  printTemperature(insideThermometer); // Use a simple function to print out the data



}

void printTemperature(DeviceAddress deviceAddress)
{
  // method 1 - slower
  //Serial.print("Temp C: ");
  //Serial.print(sensors.getTempC(deviceAddress));
  //Serial.print(" Temp F: ");
  //Serial.print(sensors.getTempF(deviceAddress)); // Makes a second call to getTempC and then converts to Fahrenheit
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_D >= interval) {
    previousMillis_D = currentMillis;


    // method 2 - faster
    float tempC = sensors.getTempC(deviceAddress);
    if (tempC == DEVICE_DISCONNECTED_C)
    {
      Serial.println("Error: Could not read temperature data");
      return;
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    // Print a message to the LCD.
    lcd.print(F("Temp C:"));
    lcd.print(tempC);
    Serial.print("Temp C: ");
    Serial.println(tempC);
    int temper_C = tempC;
    lcd.setCursor(0, 0);
    if (temper_C > 38) {
      digitalWrite(Fan, LOW);
      lcd.print("Temp High FAN ON");
    }
    if (temper_C < 36) {
      digitalWrite(Fan, HIGH);
      lcd.print("Temp LOW FAN OFF");
    }
  }
}

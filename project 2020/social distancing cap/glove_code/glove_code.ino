#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <SPI.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#include <SoftwareSerial.h>

SoftwareSerial mySerial(A2, A3); // RX, TX

void setup() {
  mySerial.begin(9600);
  mySerial.println("Adafruit MLX90614 test");
  mlx.begin();
 
}

void loop() {
//  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC());
//  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
//  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF());
//  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
//  Serial.println();
  float temp = mlx.readObjectTempF();
 
  String  mystring = String(temp);
mySerial.println(mystring);
  delay(500);
}

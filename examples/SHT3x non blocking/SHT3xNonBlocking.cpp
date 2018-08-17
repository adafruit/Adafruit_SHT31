/*************************************************** 
  This is an example for the SHT3x Humidity & Temp Sensor

  These sensors use I2C to communicate, 2 pins are required to  
  interface
  By Leonardo Bispo 08/2018
 ****************************************************/
 
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup() {
  Serial.begin(9600);

  while (!Serial)
    delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("SHT31 test");
  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
}


void loop() {
  //readTemperature() and sht31.readHumidity() have a 500msec delay between them
  //it results in a 1 second blocking function, lets remove it:
  //float t = sht31.readTemperature();
  //float h = sht31.readHumidity();
  
  sht31.requestTempHum();                   //user needs to handle the time between requesting and reading
  delay(500);
  sht31.readTemperatureAndHumidity(t, h);

  if (! isnan(t)) {  // check if 'is not a number'
    Serial.print("Temp *C = "); Serial.println(t);
  } else { 
    Serial.println("Failed to read temperature");
  }
  
  if (! isnan(h)) {  // check if 'is not a number'
    Serial.print("Hum. % = "); Serial.println(h);
  } else { 
    Serial.println("Failed to read humidity");
  }
  Serial.println();
  delay(1000);
}

/*************************************************** 
  This is a library for the SHT31 Digital Humidity & Temp Sensor

  Designed specifically to work with the SHT31 Digital sensor from Adafruit
  ----> https://www.adafruit.com/products/2857

  These sensors use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/


#include "Adafruit_SHT31.h"

Adafruit_SHT31::Adafruit_SHT31() {
}


boolean Adafruit_SHT31::begin(uint8_t i2caddr) {
  Wire.begin();
  _i2caddr = i2caddr;
  reset();
  //return (readStatus() == 0x40);
  return true;
}

uint16_t Adafruit_SHT31::readStatus(void) {
  writeCommand(SHT31_READSTATUS);
  Wire.requestFrom(_i2caddr, (uint8_t)3);
  uint16_t stat = Wire.read();
  stat <<= 8;
  stat |= Wire.read();
  Serial.println(stat, HEX);
  return stat;
}

void Adafruit_SHT31::reset(void) {
  writeCommand(SHT31_SOFTRESET);
  delay(10);
}

void Adafruit_SHT31::heater(boolean h) {
  if (h)
    writeCommand(SHT31_HEATEREN);
  else
    writeCommand(SHT31_HEATERDIS);
}


float Adafruit_SHT31::readTemperature(void) {
  readTempHum();

  return temp;
}
  

float Adafruit_SHT31::readHumidity(void) {
  readTempHum();

  return humidity;
}


boolean Adafruit_SHT31::readTempHum(void) {
  uint8_t readbuffer[6];

  writeCommand(SHT31_MEAS_HIGHREP);
  
  delay(500);
  Wire.requestFrom(_i2caddr, (uint8_t)6);
  if (Wire.available() != 6) 
    return false;
  for (uint8_t i=0; i<6; i++) {
    readbuffer[i] = Wire.read();
  //  Serial.print("0x"); Serial.println(readbuffer[i], HEX);
  }
  uint16_t ST, SRH;
  ST = readbuffer[0];
  ST <<= 8;
  ST |= readbuffer[1];
  SRH = readbuffer[3];
  SRH <<= 8;
  SRH |= readbuffer[4];
 // Serial.print("ST = "); Serial.println(ST);
  double stemp = ST;
  stemp *= 175;
  stemp /= 0xffff;
  stemp = -45 + stemp;
  temp = stemp;
  
//  Serial.print("SRH = "); Serial.println(SRH);
  double shum = SRH;
  shum *= 100;
  shum /= 0xFFFF;
  
  humidity = shum;
  
  return true;
}

void Adafruit_SHT31::writeCommand(uint16_t cmd) {
  Wire.beginTransmission(_i2caddr);
  Wire.write(cmd >> 8);
  Wire.write(cmd & 0xFF);
  Wire.endTransmission();  
}


/*********************************************************************/

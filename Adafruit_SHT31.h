/*!
 *  @file Adafruit_SHT31.h
 *
 *  This is a library for the SHT31 Digital Humidity & Temp Sensor
 *
 *  Designed specifically to work with the  Digital Humidity & Temp Sensor
 *  -----> https://www.adafruit.com/product/2857
 *
 *  These sensors use I2C to communicate, 2 pins are required to interface
 *
 *  Adafruit invests time and resources providing this open source code,
 *  please support Adafruit andopen-source hardware by purchasing products
 *  from Adafruit!
 *
 *  Limor Fried/Ladyada (Adafruit Industries).
 *
 *  BSD license, all text above must be included in any redistribution
 */

#ifndef ADAFRUIT_SHT31_H
#define ADAFRUIT_SHT31_H

#include "Arduino.h"
#include "Wire.h"

#define SHT31_DEFAULT_ADDR 0x44 /**< SHT31 Default Address */
#define SHT31_MEAS_HIGHREP_STRETCH                                             \
  0x2C06 /**< Measurement High Repeatability with Clock Stretch Enabled */
#define SHT31_MEAS_MEDREP_STRETCH                                              \
  0x2C0D /**< Measurement Medium Repeatability with Clock Stretch Enabled */
#define SHT31_MEAS_LOWREP_STRETCH                                              \
  0x2C10 /**< Measurement Low Repeatability with Clock Stretch Enabled*/
#define SHT31_MEAS_HIGHREP                                                     \
  0x2400 /**< Measurement High Repeatability with Clock Stretch Disabled */
#define SHT31_MEAS_MEDREP                                                      \
  0x240B /**< Measurement Medium Repeatability with Clock Stretch Disabled */
#define SHT31_MEAS_LOWREP                                                      \
  0x2416 /**< Measurement Low Repeatability with Clock Stretch Disabled */
#define SHT31_READSTATUS 0xF32D  /**< Read Out of Status Register */
#define SHT31_CLEARSTATUS 0x3041 /**< Clear Status */
#define SHT31_SOFTRESET 0x30A2   /**< Soft Reset */
#define SHT31_HEATEREN 0x306D    /**< Heater Enable */
#define SHT31_HEATERDIS 0x3066   /**< Heater Disable */

extern TwoWire Wire; /**< Forward declarations of Wire for board/variant
                        combinations that don't have a default 'Wire' */

/**
 * Driver for the Adafruit SHT31-D Temperature and Humidity breakout board.
 */
class Adafruit_SHT31 {
public:
  /**
   *  Constructor.
   */
  Adafruit_SHT31(TwoWire *theWire = &Wire);

  /**
   * Initialises the I2C bus, and assigns the I2C address to us.
   *
   * @param i2caddr   The I2C address to use for the sensor.
   *
   * @return True if initialisation was successful, otherwise False.
   */
  bool begin(uint8_t i2caddr = SHT31_DEFAULT_ADDR);

  /**
   * Gets a single temperature reading from the sensor.
   *
   * @return A float value indicating the temperature.
   */
  float readTemperature(void);

  /**
   * Gets a single relative humidity reading from the sensor.
   *
   * @return A float value representing relative humidity.
   */
  float readHumidity(void);

  /**
   * Gets the current status register contents.
   *
   * @return The 16-bit status register.
   */
  uint16_t readStatus(void);

  /**
   * Performs a reset of the sensor to put it into a known state.
   */
  void reset(void);

  /**
   * Enables or disabled the heating element.
   *
   * @param h True to enable the heater, False to disable it.
   */
  void heater(bool h);

  TwoWire *_wire; /**< Wire object */

private:
  /**
   * Placeholder to track humidity internally.
   */
  float humidity;

  /**
   * Placeholder to track temperature internally.
   */
  float temp;

  /**
   * Placeholder to track the I2C address.
   */
  uint8_t _i2caddr;

  /**
   * Internal function to perform a temp + humidity read.
   *
   * @return True if successful, otherwise false.
   */
  bool readTempHum(void);

  /**
   * Internal function to perform and I2C write.
   *
   * @param cmd   The 16-bit command ID to send.
   */
  void writeCommand(uint16_t cmd);

  /**
   * Internal function to read data over the I2C bus.
   *
   * @return True if successful, otherwise False.
   */
  bool readData(void);
};

#endif

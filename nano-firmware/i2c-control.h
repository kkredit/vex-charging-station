/*
 * @file i2c-control.h
 * 
 * @brief I2C communication header file
 */

#ifndef __I2C_HDR__
#define __I2C_HDR__

#include <Arduino.h>

class I2c_Controller
{
public:
  I2c_Controller() {};
  void init();
  bool updateVoltage(unsigned short voltage);

private:
  int m_address;
};

#endif


/*
 * @file i2c-control.h
 * 
 * @brief I2C communication header file
 */

#ifndef __I2C_HDR__
#define __I2C_HDR__

#include <Arduino.h>
#include "configuration.h"

class I2c_Controller
{
public:
  I2c_Controller();
  void init(Station_Status_t *pStatus);
  bool getUpdate();
  bool checkColorScheme();
  void updateColorScheme();

private:
  Station_Status_t *m_pStatus;
  int m_address;
  bool m_initialized;
};

#endif


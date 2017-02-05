/*
 * @file i2c-control.cpp
 * 
 * @brief I2C communication implementation file
 */

#include "i2c-control.h"
#include "configuration.h"
#include <Arduino.h>
#include <Wire.h>

/* Function definitions */
void I2c_Controller::init() {
  m_isMaster = false;
  if(m_isMaster) {
    Wire.begin();
  }
  else {
    Wire.begin(1);
  }

  memset(&m_latestMessage, 0, sizeof(m_latestMessage));
}

bool I2c_Controller::hasMessage() {
  return false;
}

message_t * I2c_Controller::getMessage() {
  return &m_latestMessage;
}

void I2c_Controller::sendVoltage(unsigned short voltage) {
  message_t msg = {
    .id = MSGID_VOLT_READING,
    .data = voltage,
  };
}


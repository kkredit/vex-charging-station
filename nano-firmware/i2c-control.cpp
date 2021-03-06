/*
 * @file i2c-control.cpp
 * 
 * @brief I2C communication implementation file
 */

#include "i2c-control.h"
#include <Wire.h>

/* Globals declarations, for use in interrupt handlers */
extern Station_Status_t g_status;
static volatile bool g_highest;
static volatile uint8_t g_color_scheme;

/* Function declarations */
static void requestHandler();
static void receiveHandler(int num_bytes);

/* Function definitions */
I2c_Controller::I2c_Controller() {
  m_pStatus = NULL;
  m_address = 0;
  m_initialized = false;
  g_highest = false;
}

void I2c_Controller::init(Station_Status_t *pStatus) {
  m_pStatus = pStatus;
  INIT_INPUT_PULLUP(PIN_ADDR_0);
  INIT_INPUT_PULLUP(PIN_ADDR_1);
  INIT_INPUT_PULLUP(PIN_ADDR_2);
  m_address = (LOW == digitalRead(PIN_ADDR_0))
              + 2 * (LOW == digitalRead(PIN_ADDR_1))
              + 4 * (LOW == digitalRead(PIN_ADDR_2));

  Wire.setClock(I2C_FREQUENCY);
  if(0 == m_address) {
    Wire.begin();
    g_highest = true;
  }
  else {
    Wire.begin(m_address);
    Wire.onRequest(requestHandler);
    Wire.onReceive(receiveHandler);
    g_highest = false;
  }
  g_color_scheme = g_status.color_scheme;
  m_initialized = true;
}

bool I2c_Controller::getUpdate() {
  bool retval = true;
  if(m_initialized) {
    if(0 == m_address) {
      /* If master, get voltages from others, tell the highest voltage 
       * that it is highest */
      static uint8_t reigning_highest_controller = 0;
      uint16_t current_highest_voltage = m_pStatus->voltage;
      uint8_t current_highest_controller = 0;
      uint16_t this_voltage;
      for(uint8_t i = 1; i <= MAX_NUM_SLAVES; i++) {
        Wire.beginTransmission(i);
        if(Wire.endTransmission() == 0) {
          Serial.print("Connected to I2C slave ");
          Serial.print(i);
          Serial.print("\n");
          if(2 == Wire.requestFrom(i, 2u)) {
            this_voltage = Wire.read() + (256 * Wire.read());
            Serial.print("Slave ");
            Serial.print(i);
            Serial.print(" voltage is ");
            Serial.print(this_voltage);
            Serial.print("\n");
            if(this_voltage > current_highest_voltage) {
              current_highest_voltage = this_voltage;
              current_highest_controller = i;
            }
          }
        }
      }
  
      if(current_highest_controller != reigning_highest_controller) {
        if(0 == reigning_highest_controller) {
          g_highest = false;
        }
        else {
          Wire.beginTransmission(reigning_highest_controller);
          Wire.write(CMC_NOT_HIGHEST_VOLTAGE);
          Wire.endTransmission();
        }
  
        if(0 == current_highest_controller) {
          g_highest = true;
        }
        else {
          Wire.beginTransmission(current_highest_controller);
          Wire.write(CMC_HIGHEST_VOLTAGE);
          Wire.endTransmission();
        }
      }
    }
    retval = g_highest;
  }
  return retval;
}

bool I2c_Controller::checkColorScheme() {
  bool retval = false;
  if(m_initialized) {
    return (m_pStatus->color_scheme != g_color_scheme);
  }
  return retval;
}

void I2c_Controller::updateColorScheme() {
  if(m_initialized) {
    if(0 == m_address) {
      /* If master, tell others what the new color is */
      for(uint8_t i = 1; i <= MAX_NUM_SLAVES; i++) {
        Wire.beginTransmission(i);
        Wire.write(CMC_NEW_COLOR_SCHEME);
        Wire.write(m_pStatus->color_scheme);
        Wire.endTransmission();
      }
    }
  }
}

static void requestHandler() {
  Wire.write((uint8_t *)&g_status.voltage, 2);
}

static void receiveHandler(int num_bytes) {
  while(Wire.available()) {
    switch(Wire.read()) {
      case CMC_HIGHEST_VOLTAGE:
        g_highest = true;
        break;
      case CMC_NOT_HIGHEST_VOLTAGE:
        g_highest = false;
        break;
      case CMC_NEW_COLOR_SCHEME:
        g_color_scheme = Wire.read();
      default:
        break;
    }
  }
}


/*
 * @file i2c-control.cpp
 * 
 * @brief I2C communication implementation file
 */

#include "i2c-control.h"
#include "configuration.h"
#include <Wire.h>

/* Globals declarations, for use in interrupt handlers */
volatile uint16_t g_voltage;
volatile bool g_highest;

/* Function declarations */
static void requestHandler();
static void receiveHandler(int num_bytes);

/* Function definitions */
void I2c_Controller::init() {
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

  g_voltage = 0;
}

bool I2c_Controller::updateVoltage(unsigned short voltage) {
  g_voltage = voltage;
  if(0 == m_address) {
    /* If master, get voltages from others, tell the highest voltage 
     *  that it is highest
     */
    static uint8_t reigning_highest_controller = 0;
    uint16_t current_highest_voltage = g_voltage;
    uint8_t current_highest_controller = 0;
    uint16_t this_voltage;
    for(uint8_t i = 0; i < MAX_NUM_SLAVES; i++) {
      if(2 == Wire.requestFrom(i + 1, 2)) {
        this_voltage = Wire.read() * 256 + Wire.read();
        if(this_voltage > current_highest_voltage) {
          current_highest_voltage = this_voltage;
          current_highest_controller = i;
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
        Wire.beginTransmission(reigning_highest_controller);
        Wire.write(CMC_HIGHEST_VOLTAGE);
        Wire.endTransmission();
      }
    }
  }
  return g_highest;
}

static void requestHandler() {
  Wire.write(g_voltage);
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
      default:
        break;
    }
  }
}


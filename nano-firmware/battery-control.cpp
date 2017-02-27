/*
 * @file battery-control.cpp
 * 
 * @brief Battery and charger circuit control implementation file
 */

#include <Arduino.h>
#include "battery-control.h"

/* Function definitions */
void Battery_Controller::init(Station_Status_t *pStatus) {
  m_pStatus = pStatus;
  pinMode(PIN_VOLTAGE_BATTERY, INPUT);
  pinMode(PIN_CURRENT_DRAW, INPUT);
}

uint16_t Battery_Controller::readBatteryVoltage() {
  return analogRead(PIN_VOLTAGE_BATTERY);
}

uint16_t Battery_Controller::readCurrentDraw() {
  return analogRead(PIN_CURRENT_DRAW);
}


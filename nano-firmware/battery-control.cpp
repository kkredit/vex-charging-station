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
  pinMode(PIN_VOLTAGE_CHARGER, INPUT);
  pinMode(PIN_CURRENT_DRAW, INPUT);
  INIT_OUTPUT_LOW(PIN_CONNECT_LOAD);
  INIT_OUTPUT_LOW(PIN_CONNECT_CHARGER);
}

uint16_t Battery_Controller::readBatteryVoltage() {
  return analogRead(PIN_VOLTAGE_BATTERY);
}

uint16_t Battery_Controller::readChargerVoltage() {
  return analogRead(PIN_VOLTAGE_CHARGER);
}

uint16_t Battery_Controller::readCurrentDraw() {
  return analogRead(PIN_CURRENT_DRAW);
}

void Battery_Controller::setLoadConnected(bool setval) {
  digitalWrite(PIN_CONNECT_LOAD, setval);
}

void Battery_Controller::setChargerConnected(bool setval) {
  digitalWrite(PIN_CONNECT_CHARGER, setval);
}


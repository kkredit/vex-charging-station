/*
 * @file battery-control.cpp
 * 
 * @brief Battery and charger circuit control implementation file
 */

#include "battery-control.h"
#include "configuration.h"
#include <Arduino.h>

/* Function definitions */
void Battery_Controller::init() {
  pinMode(PIN_VOLTAGE_BATTERY, INPUT);
  pinMode(PIN_VOLTAGE_CHARGER, INPUT);
}

unsigned short Battery_Controller::readVoltage() {
  return analogRead(PIN_VOLTAGE_BATTERY);
}


/*
 * @file battery-control.h
 * 
 * @brief Battery and charger circuit control header file
 */

#ifndef __BATTERY_HDR__
#define __BATTERY_HDR__

#include "configuration.h"

class Battery_Controller
{
public:
  Battery_Controller() {};
  void init(Station_Status_t *pStatus);
  uint16_t readBatteryVoltage();
  uint16_t readCurrentDraw();

private:
  Station_Status_t *m_pStatus;
};

#endif


/*
 * @file battery-control.h
 * 
 * @brief Battery and charger circuit control header file
 */

#ifndef __BATTERY_HDR__
#define __BATTERY_HDR__

class Battery_Controller
{
public:
  Battery_Controller() {};
  void init();
  unsigned short readVoltage();

private:
};

#endif

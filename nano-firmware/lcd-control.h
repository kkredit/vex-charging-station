/*
 * @file lcd-control.h
 * 
 * @brief LCD screen control header file
 */

#ifndef __LCD_HDR__
#define __LCD_HDR__

#include <LiquidCrystal.h>

class Lcd_Controller
{
public:
  Lcd_Controller() {};
  void init();
  void updateBatteryVoltage(unsigned short voltage);
  void printBottomLine(char *str);

private:
  LiquidCrystal *lcd;
  unsigned short m_voltage;
  char *m_bottomLine;
  void updateScreen();
  unsigned short getVoltageUpper();
  unsigned short getVoltageLower();
};

#endif


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
  void updateBatteryVoltage(uint16_t voltage);
  void printBottomLine(char *str);
  void checkColor();

private:
  LiquidCrystal *m_lcd;
  uint16_t m_voltage;
  char *m_bottomLine;
  void updateScreen();
  uint16_t getVoltageUpper();
  uint16_t getVoltageLower();
};

#endif


/*
 * @file lcd-control.h
 * 
 * @brief LCD screen control header file
 */

#ifndef __LCD_HDR__
#define __LCD_HDR__

#include <LiquidCrystal.h>
#include "configuration.h"

class Lcd_Controller
{
public:
  Lcd_Controller() {};
  void init(Station_Status_t *pStatus);
  void updateScreen();
  void printBottomLine(char *str);
  void checkColor();

private:
  Station_Status_t *m_pStatus;
  LiquidCrystal *m_lcd;
  uint16_t getVoltageUpper();
  uint16_t getVoltageLower();
};

#endif


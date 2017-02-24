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
  void checkScroll();
  void checkColor();

private:
  Station_Status_t *m_pStatus;
  LiquidCrystal *m_lcd;
  char m_bottomLine[LCD_BOTTOM_LINE_MAX_LEN];
  uint8_t m_bottomLineIndex;
  uint8_t m_bottomLineLen;
  uint16_t getVoltageUpper();
  uint16_t getVoltageLower();
  uint16_t getCurrent();
  uint16_t getPercent();
  char *getTimeStr();
  char *getBottomLineSubstr();
};

#endif


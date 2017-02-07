/*
 * @file lcd-control.cpp
 * 
 * @brief LCD screen control implementation file
 */

#include "lcd-control.h"
#include "configuration.h"
#include <Arduino.h>

#define ONE_VOLT (1024 / 5)

/* Function definitions */
void Lcd_Controller::init() {
  INIT_OUTPUT_LOW(PIN_LCD_PWM_R);
  INIT_OUTPUT_LOW(PIN_LCD_PWM_G);
  INIT_OUTPUT_LOW(PIN_LCD_PWM_B);

  lcd = new LiquidCrystal(PIN_LCD_TEXT_RS,
                          PIN_LCD_TEXT_ENABLE,
                          PIN_LCD_TEXT_D4,
                          PIN_LCD_TEXT_D5,
                          PIN_LCD_TEXT_D6,
                          PIN_LCD_TEXT_D7);
  lcd->begin(LCD_NUM_COLS, LCD_NUM_ROWS);
  lcd->clear();
  lcd->noCursor();
  lcd->noBlink();
  lcd->noAutoscroll();
  lcd->leftToRight();

  m_voltage = 0;
}

void Lcd_Controller::updateBatteryVoltage(unsigned short voltage) {
  m_voltage = voltage;
  lcd->clear();
  lcd->print("VOLTAGE: ");
  lcd->print(this->getVoltageUpper());
  lcd->print(".");
  lcd->print(this->getVoltageLower());
  lcd->print(" V");
}

unsigned short Lcd_Controller::getVoltageUpper() {
  return m_voltage / ONE_VOLT;
}

unsigned short Lcd_Controller::getVoltageLower() {
  return ((m_voltage % ONE_VOLT) * 100u) / ONE_VOLT;
}


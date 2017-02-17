/*
 * @file lcd-control.cpp
 * 
 * @brief LCD screen control implementation file
 */

#include "lcd-control.h"
#include "configuration.h"
#include <Arduino.h>

#define ONE_VOLT 222

/* Function definitions */
void Lcd_Controller::init() {
  INIT_OUTPUT_LOW(PIN_LCD_PWM_R);
  INIT_OUTPUT_LOW(PIN_LCD_PWM_G);
  INIT_OUTPUT_LOW(PIN_LCD_PWM_B);

  m_lcd = new LiquidCrystal(PIN_LCD_TEXT_RS,
                            PIN_LCD_TEXT_ENABLE,
                            PIN_LCD_TEXT_D4,
                            PIN_LCD_TEXT_D5,
                            PIN_LCD_TEXT_D6,
                            PIN_LCD_TEXT_D7);
  m_lcd->begin(LCD_NUM_COLS, LCD_NUM_ROWS);
  m_lcd->clear();
  m_lcd->noCursor();
  m_lcd->noBlink();
  m_lcd->noAutoscroll();
  m_lcd->leftToRight();
  m_lcd->print("Initializing");

  m_voltage = 0;
  m_bottomLine = "";
}

void Lcd_Controller::updateBatteryVoltage(uint16_t voltage) {
  m_voltage = voltage;
  this->updateScreen();
}

void Lcd_Controller::printBottomLine(char *str) {
  m_bottomLine = str;
  this->updateScreen();
}

void Lcd_Controller::updateScreen() {
  m_lcd->clear();
  m_lcd->setCursor(0, 0);
  m_lcd->print("VOLTAGE: ");
  m_lcd->print(this->getVoltageUpper());
  m_lcd->print(".");
  m_lcd->print(this->getVoltageLower());
  m_lcd->print(" V");
  m_lcd->setCursor(0, 1);
  m_lcd->print(m_bottomLine);
}

uint16_t Lcd_Controller::getVoltageUpper() {
  return m_voltage / ONE_VOLT;
}

uint16_t Lcd_Controller::getVoltageLower() {
  return ((m_voltage % ONE_VOLT) * 100u) / ONE_VOLT;
}


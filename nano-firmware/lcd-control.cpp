/*
 * @file lcd-control.cpp
 * 
 * @brief LCD screen control implementation file
 */

#include "lcd-control.h"
#include <Arduino.h>

#define ONE_VOLT 222

/* Function definitions */
void Lcd_Controller::init(Station_Status_t *pStatus) {
  m_pStatus = pStatus;
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
  if(m_pStatus->error_vector) {
    if(m_pStatus->error_vector & ERR_CHARGER_VOLTAGE) {
      m_lcd->print("Bad charger!");
    }
  }
  else {
    // TODO fill in percent charged, current draw, ETA
  }
}

void Lcd_Controller::checkColor() {
  static unsigned long color_ts = 0;
  static const unsigned pin_color[] = 
      {PIN_LCD_PWM_R, PIN_LCD_PWM_G, PIN_LCD_PWM_B};
  static int pwm_color[] = {175, 150, 125};
  static bool dir_color[] = {true, true, true};

  if(color_ts + COLOR_CHANGE_LATENCY <= millis()) {
    color_ts = millis();
    unsigned i = random(0, 3);
    pwm_color[i] += (dir_color[i] ? COLOR_CHANGE_GRAN : -COLOR_CHANGE_GRAN);
    pwm_color[i] += random(-COLOR_CHANGE_GRAN, COLOR_CHANGE_GRAN + 1);
    analogWrite(pin_color[i], pwm_color[i]);
    if(COLOR_MIN_VAL >= pwm_color[i]) {
      dir_color[i] = true;
    }
    else if(COLOR_MAX_VAL <= pwm_color[i]) {
      dir_color[i] = false;
    }
  }
}

uint16_t Lcd_Controller::getVoltageUpper() {
  return m_pStatus->voltage / ONE_VOLT;
}

uint16_t Lcd_Controller::getVoltageLower() {
  return ((m_pStatus->voltage % ONE_VOLT) * 100u) / ONE_VOLT;
}


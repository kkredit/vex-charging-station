/*
 * @file lcd-control.cpp
 * 
 * @brief LCD screen control implementation file
 */

#include "lcd-control.h"
#include <Arduino.h>
#include <string.h>

#define ONE_VOLT 56
#define MICROAMPS_PER_ADC 2000lu
#define MICROA_PER_MILLIA 1000lu

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

  m_colorScheme[0] = cs_registry[m_pStatus->color_scheme].primary;
  m_colorScheme[1] = cs_registry[m_pStatus->color_scheme].secondary;
  m_colorScheme[2] = cs_registry[m_pStatus->color_scheme].tertiary;
  memset(m_bottomLine, 0, sizeof(m_bottomLine));
  m_bottomLineIndex = 0;
  m_bottomLineLen = 1;
}

void Lcd_Controller::updateScreen() {
  m_lcd->clear();
  m_lcd->print("Voltage: ");
  m_lcd->print(getVoltageStr());
  m_lcd->print(" V");
  m_lcd->setCursor(0, 1);
  if(m_pStatus->error_vector) {
    m_bottomLineIndex = 0;
    if(m_pStatus->error_vector & ERR_CHARGER_VOLTAGE) {
      m_bottomLineLen = snprintf(m_bottomLine, LCD_BOTTOM_LINE_MAX_LEN,
                                 "Bad charger!     ");
    }
    else {
      m_bottomLineLen = snprintf(m_bottomLine, LCD_BOTTOM_LINE_MAX_LEN,
                                 "Reset board");
    }
  }
  else if(NO_BATTERY_THRESHOLD < m_pStatus->voltage) {
    m_bottomLineLen = snprintf(m_bottomLine, LCD_BOTTOM_LINE_MAX_LEN,
                               "unconnected     ");
  }
  else if(MIN_GRN_THRESHOLD < m_pStatus->voltage) {
    m_bottomLineLen = snprintf(m_bottomLine, LCD_BOTTOM_LINE_MAX_LEN,
                               "Fully charged!  ");
  }
  else {
    m_bottomLineLen = snprintf(m_bottomLine, LCD_BOTTOM_LINE_MAX_LEN,
                               "current: %umA | %u%% | %s left | ",
                               getCurrent(), getPercent(), getTimeStr());
  }
  m_lcd->print(getBottomLineSubstr());
}

void Lcd_Controller::updateColorScheme() {
  analogWrite(PIN_LCD_PWM_R, 255 - m_colorScheme[0].r);
  analogWrite(PIN_LCD_PWM_G, 255 - m_colorScheme[0].b);
  analogWrite(PIN_LCD_PWM_B, 255 - m_colorScheme[0].b);
  m_lcd->clear();
  m_lcd->write(cs_registry[m_pStatus->color_scheme].name);
  m_colorScheme[0] = cs_registry[m_pStatus->color_scheme].primary;
  m_colorScheme[1] = cs_registry[m_pStatus->color_scheme].secondary;
  m_colorScheme[2] = cs_registry[m_pStatus->color_scheme].tertiary;
}

void Lcd_Controller::checkScroll() {
  static unsigned long scroll_ts = 0;
  if(scroll_ts + LCD_SCROLL_LATENCY_MS <= millis()
     && !m_pStatus->error_vector) {
    scroll_ts = millis();
    m_bottomLineIndex++;
    m_lcd->setCursor(0, 1);
    m_lcd->print(getBottomLineSubstr());
  }
}

void Lcd_Controller::checkColor() {
  static unsigned long color_ts = 0;
  static const unsigned pin_color[] = 
      {PIN_LCD_PWM_R, PIN_LCD_PWM_G, PIN_LCD_PWM_B};

  static bool errorSet = false;
  if(m_pStatus->error_vector) {
    if(!errorSet) {
      errorSet = true;
      analogWrite(pin_color[0], 255);
      analogWrite(pin_color[1], 255);
      analogWrite(pin_color[2], 255);
    }
  }
  else if(color_ts + COLOR_CHANGE_LATENCY <= millis()) {
    color_ts = millis();
    errorSet = false;

    if(CS_RANDOM != m_pStatus->color_scheme) {
      /* Intentional color scheme */
      static uint8_t cur_color = 1;
      static uint8_t cur_target = 0;
      static int16_t cur_pos = 100; // percent of way to target
      if(0 == random(0, COLOR_SCHEM_ODDS_FLIP)) {
        uint8_t temp = cur_target;
        cur_target = cur_color;
        cur_color = temp;
        cur_pos = 100 - cur_pos;
      }
      cur_pos = min(100, cur_pos + random(1, 1 + 2 * COLOR_SCHEM_PCT_GRAN));
      /* Green has inherent advantage on the LCD, so remap R and B to 51 - 255 */
      for(uint8_t i = 0; i < 3; i++){
        int16_t val = 255 - ((100 - cur_pos) * ((int16_t *)&(m_colorScheme[cur_color]))[i] 
                             + cur_pos * ((int16_t *)&(m_colorScheme[cur_target]))[i]) / 100;
        val = min(255, val);
        val = max(0, val);
        analogWrite(pin_color[i], val);
      }
      if(100 == cur_pos) {
        cur_color = cur_target;
        cur_pos = 0;
        while(cur_color == cur_target){
          cur_target = random(0, 3);
        }
      }
    }
    else {
      /* Random colors */
      static int pwm_color[] = {175, 150, 125};
      static bool dir_color[] = {true, true, true};
      unsigned i = random(0, 3);
      pwm_color[i] += (dir_color[i] ? COLOR_RAND_CHANGE_GRAN : -COLOR_RAND_CHANGE_GRAN);
      pwm_color[i] += random(-COLOR_RAND_CHANGE_GRAN, COLOR_RAND_CHANGE_GRAN + 1);
      analogWrite(pin_color[i], pwm_color[i]);
      if(COLOR_RAND_MIN_VAL >= pwm_color[i]) {
        dir_color[i] = true;
      }
      else if(COLOR_RAND_MAX_VAL <= pwm_color[i]) {
        dir_color[i] = false;
      }
    }
  }
}

char *Lcd_Controller::getVoltageStr() {
  static char voltageStr[6] = {0};
  snprintf(voltageStr, 6, "%u.%02u",
           m_pStatus->voltage / ONE_VOLT,
           ((m_pStatus->voltage % ONE_VOLT) * 100u) / ONE_VOLT);
  return voltageStr;
}

uint16_t Lcd_Controller::getCurrent() {
  return (uint16_t)((MICROAMPS_PER_ADC * (uint32_t)m_pStatus->current) 
                    / MICROA_PER_MILLIA);
}

uint16_t Lcd_Controller::getPercent() {
  // TODO develop means of telling percent charged
  return 0;
}

char * Lcd_Controller::getTimeStr() {
  // TODO develop means of telling time remaining
  return "0:00";
}

char * Lcd_Controller::getBottomLineSubstr() {
  static char substr[LCD_NUM_COLS + 1] = {0};
  memset(substr, ' ', LCD_NUM_COLS);
  m_bottomLineIndex %= m_bottomLineLen;
  int16_t writeLen = min(LCD_NUM_COLS, m_bottomLineLen - m_bottomLineIndex);
  memcpy(substr, m_bottomLine + m_bottomLineIndex, writeLen);
  memcpy(substr + min(LCD_NUM_COLS, writeLen),
         m_bottomLine, max(0, LCD_NUM_COLS - writeLen));
  return substr;
}


/*
 * @file led-control.cpp
 * 
 * @brief LED control implementation file
 */

#include "led-control.h"
#include "configuration.h"
#include <Arduino.h>

/* Function definitions */
void Led_Controller::init() {
  INIT_OUTPUT_LOW(PIN_LED_RED);
  INIT_OUTPUT_LOW(PIN_LED_GRN);

  m_isBlinking   = false;
  m_green        = false;
  m_greenCurrent = false;
  m_red          = false;
  m_redCurrent   = false;
  m_err          = false;
}

void Led_Controller::turnOff() {
  if(!m_err) {
    digitalWrite(PIN_LED_GRN, false);
    digitalWrite(PIN_LED_RED, false);
    m_isBlinking   = false;
    m_green        = false;
    m_greenCurrent = false;
    m_red          = false;
    m_redCurrent   = false;
    m_greenCurrent = false;
  }
}

void Led_Controller::setRed() {
  if(!m_err && (m_green != false || m_red != true)) {
    digitalWrite(PIN_LED_GRN, false);
    digitalWrite(PIN_LED_RED, true);
    m_green        = false;
    m_greenCurrent = false;
    m_red          = true;
    m_redCurrent   = true;
  }
}

void Led_Controller::setGrn() {
  if(!m_err && (m_green != true || m_red != false)) {
    digitalWrite(PIN_LED_GRN, true);
    digitalWrite(PIN_LED_RED, false);
    m_green        = true;
    m_greenCurrent = true;
    m_red          = false;
    m_redCurrent   = false;
  }
}

void Led_Controller::setErr() {
  m_err = true;
  m_isBlinking = false;
  digitalWrite(PIN_LED_GRN, false);
  digitalWrite(PIN_LED_RED, false);
  m_greenCurrent = false;
  m_redCurrent = false;
}

void Led_Controller::clearErr() {
  m_err = false;
}

void Led_Controller::setBlinking(bool setval) {
  if(!m_err) {
    m_isBlinking = setval;
    if(!setval) {
      if(m_green != m_greenCurrent) {
        m_greenCurrent = m_green;
        digitalWrite(PIN_LED_GRN, m_green);
      }
      if(m_red != m_redCurrent) {
        m_redCurrent = m_red;
        digitalWrite(PIN_LED_RED, m_red);
      }
    }
  }
}

void Led_Controller::checkBlink() {
  static unsigned long blink_ts = 0;
  if(m_err) {
    if(m_redCurrent 
       && blink_ts + BLINKING_PERIOD_ERR_ON < millis()) {
      blink_ts = millis();
      m_redCurrent = false;
      digitalWrite(PIN_LED_RED, m_redCurrent);
    }
    else if (!m_redCurrent
             && blink_ts + BLINKING_PERIOD_ERR_OFF < millis()) {
      blink_ts = millis();
      m_redCurrent = true;
      digitalWrite(PIN_LED_RED, m_redCurrent);
    }
  }
  else if(m_isBlinking && blink_ts + BLINKING_PERIOD < millis()) {
    blink_ts = millis();
    m_greenCurrent = m_green && !m_greenCurrent;
    m_redCurrent = m_red && !m_redCurrent;
    digitalWrite(PIN_LED_GRN, m_greenCurrent);
    digitalWrite(PIN_LED_RED, m_redCurrent);
  }
}


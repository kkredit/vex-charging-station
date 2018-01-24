/*
 * @file led-control.cpp
 * 
 * @brief LED control implementation file
 */

#include "led-control.h"
#include <Arduino.h>

/* Function definitions */
void Led_Controller::init(Station_Status_t *pStatus) {
  m_pStatus = pStatus;
  INIT_OUTPUT_HIGH(PIN_LED_RED);
  INIT_OUTPUT_HIGH(PIN_LED_GRN);

  m_isBlinking   = false;
  m_green        = false;
  m_greenCurrent = false;
  m_red          = false;
  m_redCurrent   = false;
}

void Led_Controller::updateColors() {
  if(NO_BATTERY_THRESHOLD < m_pStatus->voltage) {
    turnOff();
  }
  else if(MIN_GRN_THRESHOLD > m_pStatus->voltage) {
    setRed();
  }
  else {
    setGrn();
  }
  setBlinking(MIN_BLINKING_THRESHOLD < m_pStatus->voltage
              && m_pStatus->is_highest);
}

void Led_Controller::checkBlink() {
  static unsigned long blink_ts = 0;
  static bool prevHadError = false;
  if(m_pStatus->error_vector) {
    if(!prevHadError) {
      prevHadError = true;
      m_isBlinking = false;
      setGrnPin(false);
      setRedPin(false);
      m_greenCurrent = false;
      m_redCurrent = false;
    }
    else {
      if(m_redCurrent 
         && blink_ts + BLINKING_PERIOD_ERR_ON < millis()) {
        blink_ts = millis();
        m_redCurrent = false;
        setRedPin(m_redCurrent);
      }
      else if (!m_redCurrent
               && blink_ts + BLINKING_PERIOD_ERR_OFF < millis()) {
        blink_ts = millis();
        m_redCurrent = true;
        setRedPin(m_redCurrent);
      }
    }
  }
  else {
    prevHadError = false;
    if(m_isBlinking && blink_ts + BLINKING_PERIOD < millis()) {
      blink_ts = millis();
      m_greenCurrent = m_green && !m_greenCurrent;
      m_redCurrent = m_red && !m_redCurrent;
      setGrnPin(m_greenCurrent);
      setRedPin(m_redCurrent);
    }
  }
}

void Led_Controller::turnOff() {
  if(!m_pStatus->error_vector) {
    setGrnPin(false);
    setRedPin(false);
    m_isBlinking   = false;
    m_green        = false;
    m_greenCurrent = false;
    m_red          = false;
    m_redCurrent   = false;
    m_greenCurrent = false;
  }
}

void Led_Controller::setRed() {
  if(!m_pStatus->error_vector && (m_green != false || m_red != true)) {
    digitalWrite(PIN_LED_GRN, true);
    setRedPin(false);
    m_green        = false;
    m_greenCurrent = false;
    m_red          = true;
    m_redCurrent   = true;
  }
}

void Led_Controller::setGrn() {
  if(!m_pStatus->error_vector && (m_green != true || m_red != false)) {
    setGrnPin(false);
    setRedPin(true);
    m_green        = true;
    m_greenCurrent = true;
    m_red          = false;
    m_redCurrent   = false;
  }
}

void Led_Controller::setBlinking(bool setval) {
  if(!m_pStatus->error_vector) {
    m_isBlinking = setval;
    if(!setval) {
      if(m_green != m_greenCurrent) {
        m_greenCurrent = m_green;
        setGrnPin(m_green);
      }
      if(m_red != m_redCurrent) {
        m_redCurrent = m_red;
        setRedPin(m_red);
      }
    }
  }
}

void Led_Controller::setRedPin(bool setval) {
  digitalWrite(PIN_LED_RED, !setval);
}

void Led_Controller::setGrnPin(bool setval) {
  digitalWrite(PIN_LED_GRN, !setval);
}


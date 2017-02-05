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
  pinMode(PIN_LED_RED, OUTPUT);
  digitalWrite(PIN_LED_RED, false);
  pinMode(PIN_LED_GRN, OUTPUT);
  digitalWrite(PIN_LED_GRN, false);

  m_isBlinking = false;
  bool m_green = false;
  bool m_red   = false;
}

void Led_Controller::turnOff() {
  digitalWrite(PIN_LED_GRN, false);
  digitalWrite(PIN_LED_RED, false);
  bool m_green = false;
  bool m_red   = false;
}

void Led_Controller::setRed() {
  digitalWrite(PIN_LED_GRN, false);
  digitalWrite(PIN_LED_RED, true);
  bool m_green = false;
  bool m_red   = true;
}

void Led_Controller::setGrn() {
  digitalWrite(PIN_LED_GRN, true);
  digitalWrite(PIN_LED_RED, false);
  bool m_green = true;
  bool m_red   = false;
}

void Led_Controller::setBlinking(bool setval) {
  m_isBlinking = setval;
}

void Led_Controller::checkBlink() {
  static bool currently_in_blink = false;
  static unsigned long blink_ts = 0;

  if(m_isBlinking) {
    if(blink_ts + BLINKING_PERIOD < millis()) {
      blink_ts = millis();
      currently_in_blink = !currently_in_blink;
      if(currently_in_blink) {
        digitalWrite(PIN_LED_GRN, false);
        digitalWrite(PIN_LED_RED, false);
      }
      else {
        digitalWrite(PIN_LED_GRN, m_green);
        digitalWrite(PIN_LED_RED, m_red);
      }
    }
  }
  else if(currently_in_blink) {
    if(m_green) {
      this->setGrn();
    }
    else if(m_red) {
      this->setRed();
    }
    currently_in_blink = false;
  }
}


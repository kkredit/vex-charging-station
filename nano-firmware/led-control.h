/*
 * @file led-control.h
 * 
 * @brief LED control header file
 */

#ifndef __LED_HDR__
#define __LED_HDR__

#include "configuration.h"

class Led_Controller
{
public:
  Led_Controller() {};
  void init(Station_Status_t *pStatus);
  void updateColors();
  void checkBlink();

private:
  Station_Status_t *m_pStatus;
  bool m_isBlinking;
  bool m_green;
  bool m_greenCurrent;
  bool m_red;
  bool m_redCurrent;
  void turnOff();
  void setRed();
  void setGrn();
  void setBlinking(bool setval);
};

#endif


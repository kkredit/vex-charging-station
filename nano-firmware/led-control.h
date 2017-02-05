/*
 * @file led-control.h
 * 
 * @brief LED control header file
 */

#ifndef __LED_HDR__
#define __LED_HDR__

class Led_Controller
{
public:
  Led_Controller() {};
  void init();
  void turnOff();
  void setRed();
  void setGrn();
  void setBlinking(bool setval);
  void checkBlink();

private:
  bool m_isBlinking;
  bool m_green;
  bool m_red;
};

#endif


/*
 * @file nano-firmware.ino
 * 
 * @brief "Main" entry point for Arduino Nano firmware; creates and manages control
 *        objects for battery, I2C, LED, and LCD control
 */

#include "configuration.h"
#include "battery-control.h"
#include "i2c-control.h"
#include "led-control.h"
#include "lcd-control.h"

/* Global variables */
Battery_Controller battery;
I2c_Controller comms;
Led_Controller leds;
Lcd_Controller lcd;

void setup() {
  /* Init control objects */
  battery.init();
  comms.init();
  leds.init();
  lcd.init();

  /* Get initial readings */
}

void loop() {
  /* Statics declarations */
  static unsigned long battery_read_ts = 0;
  unsigned short my_voltage = 0;
  unsigned short highest_other_voltage = 0;
  bool updated_voltage = false;
  
  /* Get new voltage readings every VOLTAGE_READ_PERIOD seconds */
  if(battery_read_ts + VOLTAGE_READ_PERIOD * MS_PER_SEC < millis()) {
    battery_read_ts = millis();
    my_voltage = battery.readVoltage();
    comms.sendVoltage(my_voltage);
    updated_voltage = true;
  }
  
  /* Handle any messsages */
  if(comms.hasMessage()){
    message_t *msg = comms.getMessage();
    switch(msg->id) {
      case MSGID_VOLT_READING:
        if(msg->data > highest_other_voltage) {
          highest_other_voltage = msg->data;
        }
        updated_voltage = true;
        break;
      default:
        break;
    }
  }  

  /* Update LEDs as necessary */
  if(updated_voltage) {
    if(MIN_RED_THRESHOLD > my_voltage) {
      leds.turnOff();
    }
    else if(MIN_GRN_THRESHOLD > my_voltage) {
      leds.setRed();
    }
    else {
      leds.setGrn();
    }
    leds.setBlinking((my_voltage > MIN_BLINKING_THRESHOLD
                     && my_voltage > highest_other_voltage));
  }
  leds.checkBlink();

  /* Update LCD as necessary */
}


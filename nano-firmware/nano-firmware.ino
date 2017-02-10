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

/* Local function declarations */
void readVoltage(unsigned short &voltage);

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
  static uint16_t my_voltage = 0;
  static bool is_highest = false;
  static bool updated_voltage = false;
  
  /* Get new voltage readings every VOLTAGE_READ_PERIOD seconds */
  if(battery_read_ts + VOLTAGE_READ_PERIOD * MS_PER_SEC < millis()) {
    battery_read_ts = millis();
    readVoltage(my_voltage);
    is_highest = comms.updateVoltage(my_voltage);
    updated_voltage = true;
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
    leds.setBlinking(my_voltage > MIN_BLINKING_THRESHOLD
                     && is_highest);
  }
  leds.checkBlink();

  /* Update LCD as necessary */
  if(updated_voltage) {
    lcd.updateBatteryVoltage(my_voltage);
  }
}

/* Local function definitions */
void readVoltage(uint16_t &voltage) {
  /* Battery */
  battery.setChargerConnected(false);
  battery.setLoadConnected(true);
  delay(VOLTAGE_READ_DELAY);
  voltage = battery.readBatteryVoltage();
  battery.setLoadConnected(false);
  if(BAD_CHARGER_THRESHOLD < battery.readChargerVoltage()) {
    battery.setChargerConnected(STOP_CHARGING_THRESHOLD > voltage
                                && MIN_RED_THRESHOLD < voltage);
    leds.clearErr();
  }
  else {
    /* Bad charger voltage; leave unconnected */
    leds.setErr();
    lcd.printBottomLine(BAD_VOLTAGE_STR);
  }
}


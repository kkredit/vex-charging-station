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
void readVoltage(uint16_t &voltage);

/* Global variables */
Battery_Controller battery;
I2c_Controller comms;
Led_Controller leds;
Lcd_Controller lcd;
Station_Status_t g_status;

void setup() {
  /* Init status */
  g_status.voltage = 0;
  g_status.error_vector = 0;

  /* Init control objects */
  battery.init(&g_status);
  comms.init(&g_status);
  leds.init(&g_status);
  lcd.init(&g_status);

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
    lcd.updateScreen();
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

  /* Update LCD color */
  lcd.checkColor();
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
    g_status.error_vector &= ~ERR_CHARGER_VOLTAGE;
  }
  else {
    /* Bad charger voltage; leave unconnected */
    g_status.error_vector |= ERR_CHARGER_VOLTAGE;
  }
}


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

/* Local functions declarations */
void checkErrors();

/* Global variables */
Battery_Controller battery;
I2c_Controller comms;
Led_Controller leds;
Lcd_Controller lcd;
Station_Status_t g_status;

void setup() {
  /* Init status */
  g_status.voltage = 0;
  g_status.current = 0;
  g_status.is_highest = false;
  g_status.error_vector = 0;

  /* Init control objects */
  battery.init(&g_status);
  comms.init(&g_status);
  leds.init(&g_status);
  lcd.init(&g_status);
}

void loop() {
  /* Statics declarations */
  static unsigned long battery_read_ts = 0;

  /* Get new voltage readings every VOLTAGE_READ_PERIOD seconds */
  if(battery_read_ts + VOLTAGE_READ_PERIOD * MS_PER_SEC < millis()) {
    battery_read_ts = millis();
    g_status.current = battery.readCurrentDraw();
    g_status.voltage = battery.readBatteryVoltage();
    checkErrors();
    g_status.is_highest = comms.getUpdate();
    lcd.updateScreen();
    leds.updateColors();
  }

  /* Monitor LED blink, LCD color updates */
  leds.checkBlink();
  lcd.checkScroll();
  lcd.checkColor();
}

/* Local functions definitions */
void checkErrors() {
  /* Check for ERR_CHARGER_VOLTAGE */
  if(BAD_CHARGER_THRESHOLD > g_status.voltage) {
    g_status.error_vector |= ERR_CHARGER_VOLTAGE;
  }
  else {
    g_status.error_vector &= ~ERR_CHARGER_VOLTAGE;
  }
}


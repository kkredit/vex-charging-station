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

/* ISR declarations */
static volatile bool g_buttonPressed;
static void buttonPressIsr();

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
  g_status.color_scheme = CS_DEFAULT;
  g_status.error_vector = 0;

  /* Init ISR */
  g_buttonPressed = false;
  INIT_INPUT_PULLUP(PIN_LCD_BUTTON);
  attachInterrupt(digitalPinToInterrupt(PIN_LCD_BUTTON), 
                  buttonPressIsr, FALLING);

  /* Init control objects */
  battery.init(&g_status);
  comms.init(&g_status);
  leds.init(&g_status);
  lcd.init(&g_status);
}

void loop() {
  /* Statics declarations */
  static unsigned long battery_read_ts = 0;
  static unsigned long button_press_ts = 0;

  /* Get new voltage readings every VOLTAGE_READ_PERIOD seconds */
  if(battery_read_ts + VOLTAGE_READ_PERIOD * MS_PER_SEC < millis()
     && button_press_ts + COLOR_CHANGE_SCREEN_MS < millis()) {
    battery_read_ts = millis();
    g_status.current = battery.readCurrentDraw();
    g_status.voltage = battery.readBatteryVoltage();
    checkErrors();
    g_status.is_highest = comms.getUpdate();
    lcd.updateScreen();
    leds.updateColors();
  }

  /* Handle button presses */
  if(g_buttonPressed || comms.checkColorScheme()) {
    button_press_ts = millis();
    battery_read_ts = min(0, button_press_ts + COLOR_CHANGE_SCREEN_MS 
                             - VOLTAGE_READ_PERIOD * MS_PER_SEC);
    g_buttonPressed = false;
    g_status.color_scheme++;
    g_status.color_scheme %= NUMBER_OF_CS;
    lcd.updateColorScheme();
    comms.updateColorScheme();
  }

  /* Monitor LED blink, LCD color updates */
  leds.checkBlink();
  if(button_press_ts + COLOR_CHANGE_SCREEN_MS < millis()) {
    lcd.checkScroll();
    lcd.checkColor();
  }
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

void buttonPressIsr() {
  g_buttonPressed = true;
}


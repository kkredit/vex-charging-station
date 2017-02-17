/*
 * @file configuration.h
 * 
 * @brief System configurable settings
 */

#ifndef __CONFIG_HDR__
#define __CONFIG_HDR__

#include <Arduino.h>

/* Utility macros */
#define INIT_INPUT_PULLUP(pin)  pinMode(pin, INPUT);  digitalWrite(pin, HIGH)
#define INIT_OUTPUT_LOW(pin)    pinMode(pin, OUTPUT); digitalWrite(pin, LOW)

/* Generic defines */
#define MS_PER_SEC  1000

/* Conditional compiler flags */

/* Pins */
#define PIN_CONNECT_LOAD    8
#define PIN_CONNECT_CHARGER 12

#define PIN_I2C_SDA         A4
#define PIN_I2C_SCL         A5

#define PIN_ADDR_0          A0
#define PIN_ADDR_1          A1
#define PIN_ADDR_2          A2

#define PIN_LCD_PWM_R       9
#define PIN_LCD_PWM_G       10
#define PIN_LCD_PWM_B       11

#define PIN_LED_GRN         13
#define PIN_LED_RED         A3

#define PIN_VOLTAGE_CHARGER A6
#define PIN_VOLTAGE_BATTERY A7

#define PIN_LCD_TEXT_RS     2
#define PIN_LCD_TEXT_ENABLE 3
#define PIN_LCD_TEXT_D4     4
#define PIN_LCD_TEXT_D5     5
#define PIN_LCD_TEXT_D6     6
#define PIN_LCD_TEXT_D7     7

/* Settings */
#define VOLTAGE_READ_PERIOD     5   // in seconds
#define BLINKING_PERIOD         500 // in milliseconds
#define BLINKING_PERIOD_ERR_ON  50  // in milliseconds
#define BLINKING_PERIOD_ERR_OFF 1950// in milliseconds
#define MIN_BLINKING_THRESHOLD  500 // TODO placeholder; replace with ADC reading representing ~7V
#define MIN_RED_THRESHOLD       100 // TODO placeholder; replace with ADC reading representing ~2V
#define MIN_GRN_THRESHOLD       800 // TODO placeholder; replace with ADC reading representing ~8V
#define STOP_CHARGING_THRESHOLD 900 // TODO placeholder; replace with ADC reading representing ~8.5V
#define BAD_CHARGER_THRESHOLD   500 // TODO placeholder; replace with ADC reading representing ~7V
#define VOLTAGE_READ_DELAY      50  // in ms
#define LCD_NUM_COLS            16
#define LCD_NUM_ROWS            2
#define MAX_NUM_SLAVES          7
#define I2C_FREQUENCY           100000

#define BAD_VOLTAGE_STR         "BAD CHARGER!"

typedef enum {
  CMC_HIGHEST_VOLTAGE = 0,
  CMC_NOT_HIGHEST_VOLTAGE,

  /* DO NOT MODIFY BELOW THIS LINE */
  CMC_MAX_VAL = 255,
} comms_msg_code_t;

#endif


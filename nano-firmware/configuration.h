/*
 * @file configuration.h
 * 
 * @brief System configurable settings
 */

#ifndef __CONFIG_HDR__
#define __CONFIG_HDR__

#include <Arduino.h>

/* Generic defines */
#define MS_PER_SEC  1000

/* Conditional compiler flags */

/* Pins */
#define PIN_CONNECT_LOAD    2
#define PIN_CONNECT_CHARGER 3

#define PIN_I2C_SDA         4
#define PIN_I2C_SCL         5

#define PIN_ADDR_0          6
#define PIN_ADDR_1          7
#define PIN_ADDR_2          8

#define PIN_LCD_PWM_R       9
#define PIN_LCD_PWM_G       10
#define PIN_LCD_PWM_B       11

#define PIN_LED_GRN         12
#define PIN_LED_RED         13

#define PIN_VOLTAGE_CHARGER A0
#define PIN_VOLTAGE_BATTERY A1

#define PIN_LCD_TEXT_0      A2
#define PIN_LCD_TEXT_1      A3
#define PIN_LCD_TEXT_2      A4
#define PIN_LCD_TEXT_3      A5
#define PIN_LCD_TEXT_4      A6
#define PIN_LCD_TEXT_5      A7

/* Settings */
#define VOLTAGE_READ_PERIOD     5 // in seconds
#define MIN_BLINKING_THRESHOLD  100 // TODO placeholder; replace with ADC reading representing ~7V
#define BLINKING_PERIOD         500 // in milliseconds
#define MIN_RED_THRESHOLD       100 // TODO placeholder; replace with ADC reading representing ~2V
#define MIN_GRN_THRESHOLD       100 // TODO placeholder; replace with ADC reading representing ~8V

#endif


/*
 * @file configuration.h
 * 
 * @brief System configurable settings
 */

#ifndef __CONFIG_HDR__
#define __CONFIG_HDR__

#include <Arduino.h>

/* Typedefs */

// Note: color is uint8_t, but use math that requires int16_t
typedef struct {
  int16_t r;
  int16_t g;
  int16_t b;
} rgb_t;

typedef enum {
  CS_RANDOM = 0,
  CS_GRCS,
  CS_UM,
  CS_MSU,
  CS_CHRISTMAS,
  CS_HALLOWEEN,
  CS_PATRIOTIC,
  /* Do no modify below this line */
  NUMBER_OF_CS,
} color_scheme_t;

typedef struct {
  color_scheme_t  cs;
  char            *name;
  rgb_t           primary;
  rgb_t           secondary;
  rgb_t           tertiary;
} cs_entry_t;

typedef struct {
  uint16_t  voltage;
  uint16_t  current;
  bool      is_highest;
  uint8_t   color_scheme;
  uint8_t   error_vector;
} Station_Status_t;

typedef enum {
  CMC_HIGHEST_VOLTAGE = 0,
  CMC_NOT_HIGHEST_VOLTAGE,
  CMC_NEW_COLOR_SCHEME,
} comms_msg_code_t;

/* Utility macros */
#define INIT_INPUT_PULLUP(pin)  pinMode(pin, INPUT);  digitalWrite(pin, HIGH)
#define INIT_OUTPUT_LOW(pin)    pinMode(pin, OUTPUT); digitalWrite(pin, LOW)
#define INIT_OUTPUT_HIGH(pin)   pinMode(pin, OUTPUT); digitalWrite(pin, HIGH)

/* Errors -- in order of significance */
#define ERR_CHARGER_VOLTAGE 0x1

/* Generic defines */
#define MS_PER_SEC  1000lu

/* Pins */
#define PIN_LCD_BUTTON      2
#define PIN_LCD_TEXT_RS     3
#define PIN_LCD_TEXT_ENABLE 4
#define PIN_LCD_TEXT_D4     5
#define PIN_LCD_TEXT_D5     6
#define PIN_LCD_TEXT_D6     7
#define PIN_LCD_TEXT_D7     8
#define PIN_LCD_PWM_R       9
#define PIN_LCD_PWM_G       10
#define PIN_LCD_PWM_B       11

#define PIN_LED_RED         12
#define PIN_LED_GRN         13

#define PIN_ADDR_0          A0
#define PIN_ADDR_1          A1
#define PIN_ADDR_2          A2

#define PIN_I2C_SDA         A4
#define PIN_I2C_SCL         A5

#define PIN_CURRENT_DRAW    A6
#define PIN_VOLTAGE_BATTERY A3

/* Settings */
#define VOLTAGE_READ_PERIOD     1lu   // in seconds
#define COLOR_SCHEME_DEFAULT    CS_RANDOM
#define COLOR_CHANGE_LATENCY    100lu // in milliseconds
#define COLOR_RAND_CHANGE_GRAN  2     // out of 0-255
#define COLOR_RAND_MIN_VAL      25    // out of 0-255
#define COLOR_RAND_MAX_VAL      250   // out of 0-255
#define COLOR_SCHEM_PCT_GRAN    1     // in percent
#define COLOR_SCHEM_ODDS_FLIP   100   // avg number updates between changing direction
#define COLOR_CHANGE_SCREEN_MS  2000  // in milliseconds
#define BLINKING_PERIOD         500lu // in milliseconds
#define BLINKING_PERIOD_ERR_ON  50lu  // in milliseconds
#define BLINKING_PERIOD_ERR_OFF 1950lu // in milliseconds
#define ONE_VOLT                30
#define MIN_BLINKING_THRESHOLD  (ONE_VOLT * 7)
#define MIN_GRN_THRESHOLD       (ONE_VOLT * 12)
#define BAD_CHARGER_THRESHOLD   (ONE_VOLT * 0)
#define NO_BATTERY_THRESHOLD    (ONE_VOLT * 12) // voltage is so high that must be free charger
#define VOLTAGE_READ_DELAY      50    // in ms
#define LCD_NUM_COLS            16
#define LCD_NUM_ROWS            2
#define LCD_BOTTOM_LINE_MAX_LEN 128
#define LCD_SCROLL_LATENCY_MS   1000
#define MAX_NUM_SLAVES          7
#define I2C_FREQUENCY           100000

#endif


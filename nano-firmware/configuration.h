/*
 * @file configuration.h
 * 
 * @brief System configurable settings
 */

#ifndef __CONFIG_HDR__
#define __CONFIG_HDR__

#include <Arduino.h>

/* Typedefs */
typedef struct {
  uint16_t voltage;
  uint8_t  error_vector;
} Station_Status_t;

// Note: color is uint8_t, but use math that requires int16_t
typedef struct {
  int16_t r;
  int16_t g;
  int16_t b;
} rgb_t;

typedef enum {
  CMC_HIGHEST_VOLTAGE = 0,
  CMC_NOT_HIGHEST_VOLTAGE,
} comms_msg_code_t;

/* Color settings */
//#define RANDOM_COLORS // Comment out this line and re-upload for intentional colors
#define COLOR_1 rgb_um_blue
#define COLOR_2 rgb_um_maize
#define COLOR_3 rgb_um_white

/* Generic colors according to 
 * http://www.rapidtables.com/web/color/RGB_Color.htm */
const rgb_t rgb_black   = {0  , 0  , 0  };
const rgb_t rgb_white   = {255, 255, 255};
const rgb_t rgb_red     = {255, 0  , 0  };
const rgb_t rgb_lime    = {0  , 255, 0  };
const rgb_t rgb_blue    = {0  , 0  , 255};
const rgb_t rgb_yellow  = {255, 255, 0  };
const rgb_t rgb_cyan    = {0  , 255, 255};
const rgb_t rgb_magenta = {255, 0  , 255};
const rgb_t rgb_silver  = {192, 192, 192};
const rgb_t rgb_gray    = {128, 128, 128};
const rgb_t rgb_maroon  = {128, 0  , 0  };
const rgb_t rgb_olive   = {128, 128, 0  };
const rgb_t rgb_green   = {0  , 128, 0  };
const rgb_t rgb_purple  = {128, 0  , 128};
const rgb_t rgb_teal    = {0  , 128, 128};
const rgb_t rgb_navy    = {0  , 0  , 128};
/* GRCS */
const rgb_t rgb_grcs_navy  = {0  , 46 , 72 };
const rgb_t rgb_grcs_baby  = {113, 180, 225};
const rgb_t rgb_grcs_white = rgb_white;
/* University of Michigan */
const rgb_t rgb_um_blue  = {0  , 45 , 98 };
const rgb_t rgb_um_maize = {255, 128, 6  };
const rgb_t rgb_um_white = rgb_white;
/* Michigan State University */
const rgb_t rgb_msu_green  = {4  , 30 , 4  };
const rgb_t rgb_msu_white  = rgb_gray;
const rgb_t rgb_msu_bright = {20 , 150, 20 };
/* Christmas */
const rgb_t rgb_chrs_red   = rgb_red;
const rgb_t rgb_chrs_green = {0  , 255, 0  };
const rgb_t rgb_chrs_white = rgb_white;
/* Halloween */
const rgb_t rgb_hllw_orange = {255, 64 , 0  };
const rgb_t rgb_hllw_black  = rgb_black;
const rgb_t rgb_hllw_white  = rgb_white;

/* Utility macros */
#define INIT_INPUT_PULLUP(pin)  pinMode(pin, INPUT);  digitalWrite(pin, HIGH)
#define INIT_OUTPUT_LOW(pin)    pinMode(pin, OUTPUT); digitalWrite(pin, LOW)

/* Errors -- in order of significance */
#define ERR_CHARGER_VOLTAGE 0x1

/* Generic defines */
#define MS_PER_SEC  1000lu

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
#define VOLTAGE_READ_PERIOD     5lu   // in seconds
#define COLOR_CHANGE_LATENCY    100lu // in milliseconds
#define COLOR_RAND_CHANGE_GRAN  2     // out of 0-255
#define COLOR_RAND_MIN_VAL      25    // out of 0-255
#define COLOR_RAND_MAX_VAL      250   // out of 0-255
#define COLOR_SCHEM_PCT_GRAN    1     // in percent
#define COLOR_SCHEM_ODDS_FLIP   100   // avg number updates between changing direction
#define BLINKING_PERIOD         500lu // in milliseconds
#define BLINKING_PERIOD_ERR_ON  50lu  // in milliseconds
#define BLINKING_PERIOD_ERR_OFF 1950lu // in milliseconds
#define MIN_BLINKING_THRESHOLD  500   // TODO placeholder; replace with ADC reading representing ~7V
#define MIN_RED_THRESHOLD       100   // TODO placeholder; replace with ADC reading representing ~2V
#define MIN_GRN_THRESHOLD       800   // TODO placeholder; replace with ADC reading representing ~8V
#define STOP_CHARGING_THRESHOLD 900   // TODO placeholder; replace with ADC reading representing ~8.5V
#define BAD_CHARGER_THRESHOLD   500   // TODO placeholder; replace with ADC reading representing ~7V
#define VOLTAGE_READ_DELAY      50    // in ms
#define LCD_NUM_COLS            16
#define LCD_NUM_ROWS            2
#define MAX_NUM_SLAVES          7
#define I2C_FREQUENCY           100000

#endif


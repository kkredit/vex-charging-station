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

// Note: color is uint8_t, but use math that requires int16_t
typedef struct {
  int16_t r;
  int16_t g;
  int16_t b;
} rgb_t;

/* Generic colors according to 
 * http://www.rapidtables.com/web/color/RGB_Color.htm */
#define rgb_black         {0  , 0  , 0  }
#define rgb_white         {255, 255, 255}
#define rgb_red           {255, 0  , 0  }
#define rgb_lime          {0  , 255, 0  }
#define rgb_blue          {0  , 0  , 255}
#define rgb_yellow        {255, 255, 0  }
#define rgb_cyan          {0  , 255, 255}
#define rgb_magenta       {255, 0  , 255}
#define rgb_silver        {192, 192, 192}
#define rgb_gray          {128, 128, 128}
#define rgb_maroon        {128, 0  , 0  }
#define rgb_olive         {128, 128, 0  }
#define rgb_green         {0  , 128, 0  }
#define rgb_purple        {128, 0  , 128}
#define rgb_teal          {0  , 128, 128}
#define rgb_navy          {0  , 0  , 128}
/* GRCS */
#define rgb_grcs_navy     {0  , 46 , 72 }
#define rgb_grcs_baby     {113, 180, 225}
#define rgb_grcs_white    rgb_white
/* University of Michigan */
#define rgb_um_blue       {0  , 45 , 98 }
#define rgb_um_maize      {255, 165, 30 }
#define rgb_um_white      rgb_white
/* Michigan State University */
#define rgb_msu_green     {4  , 30 , 4  }
#define rgb_msu_white     rgb_gray
#define rgb_msu_bright    {20 , 150, 20 }
/* Christmas */
#define rgb_chrs_red      rgb_red
#define rgb_chrs_green    {0  , 255, 0  }
#define rgb_chrs_white    rgb_white
/* Halloween */
#define rgb_hllw_orange   {255, 64 , 0  }
#define rgb_hllw_black    rgb_black
#define rgb_hllw_white    rgb_white
/* Patriotic */
#define rgb_pat_red       rgb_red
#define rgb_pat_white     rgb_white
#define rgb_pat_blue      rgb_blue

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

#define CS_DEFAULT CS_RANDOM

typedef struct {
  color_scheme_t  cs;
  char            *name;
  rgb_t           primary;
  rgb_t           secondary;
  rgb_t           tertiary;
} cs_entry_t;

static const cs_entry_t cs_registry[] = {
  {CS_RANDOM,     "Random",     rgb_white,        rgb_white,      rgb_white     },
  {CS_GRCS,       "GRCS",       rgb_grcs_navy,    rgb_grcs_baby,  rgb_grcs_white},
  {CS_UM,         "U of M",     rgb_um_blue,      rgb_um_maize,   rgb_um_white  },
  {CS_MSU,        "MSU",        rgb_msu_green,    rgb_msu_white,  rgb_msu_white },
  {CS_CHRISTMAS,  "Christmas",  rgb_chrs_red,     rgb_chrs_green, rgb_chrs_white},
  {CS_HALLOWEEN,  "Halloween",  rgb_hllw_orange,  rgb_hllw_black, rgb_hllw_white},
  {CS_PATRIOTIC,  "Patriotic",  rgb_pat_red,      rgb_pat_white,  rgb_pat_blue  },
};

/* Utility macros */
#define INIT_INPUT_PULLUP(pin)  pinMode(pin, INPUT);  digitalWrite(pin, HIGH)
#define INIT_OUTPUT_LOW(pin)    pinMode(pin, OUTPUT); digitalWrite(pin, LOW)

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
#define PIN_VOLTAGE_BATTERY A7

/* Settings */
#define VOLTAGE_READ_PERIOD     5lu   // in seconds
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
#define MIN_BLINKING_THRESHOLD  350   // TODO placeholder; replace with ADC reading representing ~7V
#define MIN_GRN_THRESHOLD       400   // TODO placeholder; replace with ADC reading representing ~8V
#define BAD_CHARGER_THRESHOLD   100
#define NO_BATTERY_THRESHOLD    600
#define VOLTAGE_READ_DELAY      50    // in ms
#define LCD_NUM_COLS            16
#define LCD_NUM_ROWS            2
#define LCD_BOTTOM_LINE_MAX_LEN 128
#define LCD_SCROLL_LATENCY_MS   1000
#define MAX_NUM_SLAVES          7
#define I2C_FREQUENCY           100000

#endif


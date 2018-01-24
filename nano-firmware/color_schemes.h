/*
 * @file color_schemes.h
 * 
 * @brief Contains LCD color scheme info
 */

#ifndef __COLOR_SCHEMES_HDR__
#define __COLOR_SCHEMES_HDR__

#include <Arduino.h>

/* Defines */

// Generic colors according to 
// http://www.rapidtables.com/web/color/RGB_Color.htm
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
// GRCS
#define rgb_grcs_navy     {0  , 46 , 72 }
#define rgb_grcs_baby     {113, 180, 225}
#define rgb_grcs_white    rgb_white
// University of Michigan
#define rgb_um_blue       {0  , 45 , 98 }
#define rgb_um_maize      {255, 165, 30 }
#define rgb_um_white      rgb_white
// Michigan State University
#define rgb_msu_green     {4  , 30 , 4  }
#define rgb_msu_white     rgb_gray
#define rgb_msu_bright    {20 , 150, 20 }
// Christmas
#define rgb_chrs_red      rgb_red
#define rgb_chrs_green    {0  , 255, 0  }
#define rgb_chrs_white    rgb_white
// Halloween
#define rgb_hllw_orange   {255, 64 , 0  }
#define rgb_hllw_black    rgb_black
#define rgb_hllw_white    rgb_white
// Patriotic
#define rgb_pat_red       rgb_red
#define rgb_pat_white     rgb_white
#define rgb_pat_blue      rgb_blue


/* Data */

static const cs_entry_t cs_registry[] = {
  {CS_RANDOM,     "Random",     rgb_white,        rgb_white,      rgb_white     },
  {CS_GRCS,       "GRCS",       rgb_grcs_navy,    rgb_grcs_baby,  rgb_grcs_white},
  {CS_UM,         "U of M",     rgb_um_blue,      rgb_um_maize,   rgb_um_white  },
  {CS_MSU,        "MSU",        rgb_msu_green,    rgb_msu_white,  rgb_msu_white },
  {CS_CHRISTMAS,  "Christmas",  rgb_chrs_red,     rgb_chrs_green, rgb_chrs_white},
  {CS_HALLOWEEN,  "Halloween",  rgb_hllw_orange,  rgb_hllw_black, rgb_hllw_white},
  {CS_PATRIOTIC,  "Patriotic",  rgb_pat_red,      rgb_pat_white,  rgb_pat_blue  },
};

#endif


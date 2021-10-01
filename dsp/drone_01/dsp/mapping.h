/* MICROCOSMOS - Firmware for the MICROCOSMOS Board
 * Copyright (C) 2020 Faselunare
 *
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <https://www.gnu.org/licenses/>.
 */

#ifndef __MICROCOSMOS_CONFIG__
#define __MICROCOSMOS_CONFIG__

#include "../core/menu-param.h"
#include "../core/button-mapping.h"
#include "../core/leds-mapping.h"

// EDIT THIS SECTION TO MAP DSP PARAMETERS
#define DSP "drone_001"          // (further use)
#define VERSION "0"           // (further use)
#define MENU_PAGES_LENGTH 4   // number of pages
#define PARAMS_PER_PAGE 4     // how many params are shown on a page
#define BUTTONS_MAPPING_LENGHT 10
#define MENU_PARAMS_LENGTH MENU_PAGES_LENGTH * PARAMS_PER_PAGE

#define MIDI_NOTE_ENABLED false // enable only if there are gate/note params
#define MIDI_CC_ENABLED true

// EVERY PAGE OF THE MENU MUST HAVE A STRING TITLE
const char* const PAGE_TITLES[MENU_PAGES_LENGTH] = {
  "VOICE 1",
  "VOICE 2",
  "VOICE 3",
  "DELAY"
};

// MENU PARAMETERS LIST
const MenuParam MENU_PARAMS[MENU_PARAMS_LENGTH] = {
  // faust, display, default, min, max, CC
  // DRONE
  {"V1 NOTE", "NOTE", 69, 0, 127, 21},
  {"V1 LFO FREQ", "LFO FREQ", 1, 0, 80, 22},
  {"V1 LFO DEEP", "LFO DEEP", 0, 0, 1, 23},
  {"V1 VOLUME", "VOLUME", 0.1, 0, 0.9, 24},

  {"V2 NOTE", "NOTE", 69, 0, 127, 25},
  {"V2 LFO FREQ", "LFO FREQ", 1, 0, 80, 26},
  {"V2 LFO DEEP","LFO DEEP", 0, 0, 1, 27},
  {"V2 VOLUME", "VOLUME", 0.1, 0, 0.9, 28},

  {"V3 NOTE", "NOTE", 69, 0, 127, 41},
  {"V3 LFO FREQ", "LFO FREQ", 1, 0, 80, 42},
  {"V3 LFO DEEP","LFO DEEP", 0, 0, 1, 43},
  {"V3 VOLUME", "VOLUME", 0.1, 0, 0.9, 44},

  {"TIME", "TIME", 250, 0, 1000, 45},
  {"FEEDBACK", "FEEDBACK", 0.5, 0.0, 1.0, 46},
  {"AMOUNT","AMOUNT", 0.5, 0.0, 1.0, 47},
  {"", "", 0, 0, 0, 0},
};
// END MAPPING

const ButtonMapping BUTTONS_MAPPING[BUTTONS_MAPPING_LENGHT] = {
  // encoder buttons
  {1, BUTTON_MODE_MENU_DOWN},
  {0},
  {0},
  {0},
  {0},
  // buttons
  {1, BUTTON_MODE_MENU_UP},
  {2, BUTTON_MODE_SINGLE, "gate", 64},
  {0},
  {0},
  {0},
};

// mode; param1[16]; min; max;
const LedsMapping LEDS_MAPPING[MENU_PAGES_LENGTH] = {
  {0},
  {0},
  {0},
  {0}
};

const byte FG_COLOR[3] {
  0x00, 0xFF, 0x00
};

#endif

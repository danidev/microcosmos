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
#define DSP "looper02"          // (name of the dsp on eeprom) 8 chars
#define VERSION "0"           // (further use)
#define MENU_PAGES_LENGTH 2   // number of pages
#define BUTTONS_MAPPING_LENGHT 20
#define MIDI_NOTE_ENABLED false
#define MIDI_CC_ENABLED true

#define PARAMS_PER_PAGE 4     // how many params are shown on a page
#define MENU_PARAMS_LENGTH MENU_PAGES_LENGTH * PARAMS_PER_PAGE



// EVERY PAGE OF THE MENU MUST HAVE A STRING TITLE
const char* const PAGE_TITLES[MENU_PAGES_LENGTH] = {
  "LOOPER 1",
  "LOOPER 2"
};

// MENU PARAMETERS LIST
const MenuParam MENU_PARAMS[MENU_PARAMS_LENGTH] = {
  // faust, display, default, min, max, CC
  // LOOPER
  {"read_speed_1", "SPEED 1", 31, 0.f, 127.f, 21},
  {"loop_length_1", "LENGTH 1", 127, 0, 127, 22},
  {"rate_1", "RATE 1", 1, 1, 20, 23},
  {"volume_1", "VOL 1", 127, 0.f, 127.f, 24},

  {"read_speed_2", "SPEED 2", 31, 0.f, 127.f, 41},
  {"loop_length_2", "LENGTH 2", 127, 0, 127, 42},
  {"rate_2", "RATE 2", 1, 1, 20, 43},
  {"volume_2", "VOL 2", 127, 0.f, 127.f, 44}
};
// END MAPPING

const ButtonMapping BUTTONS_MAPPING[BUTTONS_MAPPING_LENGHT] = {
  // PAGE 1
  // encoder buttons
  {0, BUTTON_MODE_MENU_DOWN},
  {0},
  {0},
  {0},
  {0},
  // buttons
  {0, BUTTON_MODE_MENU_UP},
  {0, BUTTON_MODE_SINGLE, "rec_1", 64},
  {1, BUTTON_MODE_SINGLE, "gate_1" 65},
  {1, BUTTON_MODE_SINGLE, "stutter_1", 66},
  {0},

  // PAGE 2
  // encoder buttons
  {0, BUTTON_MODE_MENU_DOWN},
  {0},
  {0},
  {0},
  {0},
  // buttons
  {0, BUTTON_MODE_MENU_UP},
  {0, BUTTON_MODE_SINGLE, "rec_2" 68},
  {1, BUTTON_MODE_SINGLE, "gate_2", 69},
  {1, BUTTON_MODE_SINGLE, "stutter_2", 70},
  {0}
};

// mode; param1[16]; min; max;
const LedsMapping LEDS_MAPPING[MENU_PAGES_LENGTH] = {
  {1, "read_index_1", 0, 48000, {0x20, 0, 0}},
  {2, "read_index_2", 0, 48000, {0, 0, 0x20}}
};

const byte FG_COLOR[3] {
  0xFF, 0x00, 0x00
};

#endif

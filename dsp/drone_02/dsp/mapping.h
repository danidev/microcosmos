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
#define DSP "drone_02"     // (further use)
#define VERSION 16            // (further use)
#define MENU_PAGES_LENGTH 1   // number of pages
#define PARAMS_PER_PAGE 4     // how many params are shown on a page
#define BUTTONS_MAPPING_LENGHT 10
#define MENU_PARAMS_LENGTH MENU_PAGES_LENGTH * PARAMS_PER_PAGE

// EVERY PAGE OF THE MENU MUST HAVE A STRING TITLE
const char* const PAGE_TITLES[MENU_PAGES_LENGTH] = {
  "MICRO:DRONE"
};

#define MIDI_NOTE_ENABLED false
#define MIDI_CC_ENABLED true

// MENU PARAMETERS LIST
const MenuParam MENU_PARAMS[MENU_PARAMS_LENGTH] = {
  // faust, display, default, min, max, CC
  {"modulator", "mod 1", 440, 0, 523.25, 21},
  {"carrier1", "car 1", 440, 0, 523.25, 22},
  {"carrier2", "car 2", 440, 0, 523.25, 23},
  {"cutoff", "cutoff", 80, 0, 523.25, 24}
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
  {0}
};

const byte FG_COLOR[3] {
  0xFF, 0xFF, 0x00
};

#endif

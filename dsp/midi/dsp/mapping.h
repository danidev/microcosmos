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
#define DSP "midi0001"          // (further use)
#define VERSION "0"           // (further use)
#define MENU_PAGES_LENGTH 1   // number of pages
#define PARAMS_PER_PAGE 4     // how many params are shown on a page
#define BUTTONS_MAPPING_LENGHT 10
#define MENU_PARAMS_LENGTH MENU_PAGES_LENGTH * PARAMS_PER_PAGE

#define MIDI_NOTE_ENABLED true
#define MIDI_CC_ENABLED true

// EVERY PAGE OF THE MENU MUST HAVE A STRING TITLE
const char* const PAGE_TITLES[MENU_PAGES_LENGTH] = {
  "MIDI"
};

// MENU PARAMETERS LIST
const MenuParam MENU_PARAMS[MENU_PARAMS_LENGTH] = {
  // faust, display, default, min, max, CC
  // MIDI
  {"duty", "duty", 0.5, 0.0, 1.0, 21},
  {"attack", "attack", 0.1, 0.0, 1.0, 22},
  {"release", "release", 0.2, 0.0, 1.0, 23},
  {"", "", 0.1, 0, 0.9, 0}
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
  {1, BUTTON_MODE_NOTE, "", 64},
  {0},
  {0},
  {0}
};

// mode; param1[16]; min; max;
const LedsMapping LEDS_MAPPING[MENU_PAGES_LENGTH] = {
  {0, "", -1, 1},
};

const byte FG_COLOR[3] {
  0xFF, 0xFF, 0xFF
};

#endif

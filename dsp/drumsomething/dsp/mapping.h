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
#define DSP "drumsome"          // (name of the dsp on eeprom) 8 chars
#define VERSION "0"           // (further use)
#define MENU_PAGES_LENGTH 1   // number of pages
#define BUTTONS_MAPPING_LENGHT 10
#define MIDI_NOTE_ENABLED false
#define MIDI_CC_ENABLED true

#define PARAMS_PER_PAGE 4     // how many params are shown on a page
#define MENU_PARAMS_LENGTH MENU_PAGES_LENGTH * PARAMS_PER_PAGE



// EVERY PAGE OF THE MENU MUST HAVE A STRING TITLE
const char* const PAGE_TITLES[MENU_PAGES_LENGTH] = {
  "Drum"
};

// MENU PARAMETERS LIST
const MenuParam MENU_PARAMS[MENU_PARAMS_LENGTH] = {
  // faust, display, default, min, max, CC
  // LOOPER
  {"kick_pitch", "KICK", 30, 0, 127, 21},
  {"", "", 127, 0, 127, 22},
  {"", "", 1, 1, 20, 23},
  {"", "", 127, 0.f, 127.f, 24},
};
// END MAPPING

const ButtonMapping BUTTONS_MAPPING[BUTTONS_MAPPING_LENGHT] = {
  // PAGE 1
  // encoder buttons
  {0, BUTTON_MODE_MENU_DOWN, "", "", 0, 0, 0, 0},
  {0, 0, "", "", 0, 0, 0, 0},
  {0, 0, "", "", 0, 0, 0, 0},
  {0, 0, "", "", 0, 0, 0, 0},
  {0, 0, "", "", 0, 0, 0, 0},
  // buttons
  {0, BUTTON_MODE_MENU_UP, "", "", 0, 0, 0, 0},
  {0, BUTTON_MODE_SINGLE, "kick_trigger", "", 1, 0, 0, 0},
  {1, BUTTON_MODE_SINGLE, "snare_trigger", "", 1, 0, 0, 0},
  {1, BUTTON_MODE_SINGLE, "hat_trigger", "", 1, 0, 0, 0},
  {0, 0, "", "", 1, 0, 0, 0},
};

// mode; param1[16]; min; max;
const LedsMapping LEDS_MAPPING[MENU_PAGES_LENGTH] = {
  {0, "read_index_1", 0, 48000, {0x20, 0, 0}}
};

const byte FG_COLOR[3] {
  0xFF, 0xFF, 0xFF
};

#endif

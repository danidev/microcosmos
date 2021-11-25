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
#define DSP "ADC_21"          // (further use)
#define VERSION 1             // (further use)
#define MENU_PAGES_LENGTH 2   // number of pages
#define PARAMS_PER_PAGE 4     // how many params are shown on a page
#define BUTTONS_MAPPING_LENGHT 10
#define MENU_PARAMS_LENGTH MENU_PAGES_LENGTH * PARAMS_PER_PAGE

// EVERY PAGE OF THE MENU MUST HAVE A STRING TITLE
const char* const PAGE_TITLES[MENU_PAGES_LENGTH] = {
  "ADC 2021 1",
  "ADC 2021 2"
};

#define MIDI_NOTE_ENABLED true
#define MIDI_CC_ENABLED true

// MENU PARAMETERS LIST
const MenuParam MENU_PARAMS[MENU_PARAMS_LENGTH] = {
  // faust, display, default, min, max, CC
  {"attack", "ATTACK", 0.1, 0.01, 1, 21},
  {"release", "RELEASE", 0.1, 0, 1, 22},
  {"cutoff", "CUTOFF", 5000, 50, 10000, 23},
  {"resonance", "RESO", 1, 1, 2, 24},
  {"LFO", "LFO", 1, 0, 80, 25},
  {"LFO->cutoff", "TO CO", 0, 0, 1, 26},
  {"LFO->pitch", "TO PITCH", 0, 0, 1, 27},
  {"", "", 0, 0}
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
  {1, BUTTON_MODE_NOTE, "", 36},
  {1, BUTTON_MODE_NOTE, "", 39},
  {1, BUTTON_MODE_NOTE, "", 43},
  {1, BUTTON_MODE_NOTE, "", 46}
};

// mode; param1[16]; min; max;
const LedsMapping LEDS_MAPPING[MENU_PAGES_LENGTH] = {
  {0}
};

const byte FG_COLOR[3] {
  0xFF, 0xFF, 0xFF
};

#endif

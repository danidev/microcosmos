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
#define DSP "syxtyof1"     // (further use)
#define VERSION 16            // (further use)
#define MENU_PAGES_LENGTH 5   // number of pages
#define PARAMS_PER_PAGE 4     // how many params are shown on a page
#define BUTTONS_MAPPING_LENGHT 10
#define MENU_PARAMS_LENGTH MENU_PAGES_LENGTH * PARAMS_PER_PAGE

// EVERY PAGE OF THE MENU MUST HAVE A STRING TITLE
const char* const PAGE_TITLES[MENU_PAGES_LENGTH] = {
  "1 OSC",
  "2 VCF",
  "3 ENV",
  "4 ENV MOD",
  "5 LFO MOD"
};

#define MIDI_NOTE_ENABLED true
#define MIDI_CC_ENABLED true

// MENU PARAMETERS LIST
const MenuParam MENU_PARAMS[MENU_PARAMS_LENGTH] = {
  // faust, display, default, min, max, CC
  // OSC
  {"duty", "PWM", 0.5, 0, 1, 21},
  {"vol_a", "SQUARE", 0.5, 0, 1, 22},
  {"vol_b", "SAW", 0.5, 0, 1, 23},
  {"vol_c", "SUB", 0.5, 0, 1, 24},
  // VCF
  {"cutoff", "CUTOFF", 5000, 50, 10000, 25},
  {"resonance", "RESONANCE", 1, 1, 5, 26},
  {"noise", "NOISE", 0.5, 0, 1, 27},
  {"", "", 0, 0},
  // ENV
  {"1a", "ATTACK", 0.02, 0.02, 2.0, 41},
  {"2d", "DECAY", 0, 0, 2.0, 42},
  {"3s", "SUSTAIN", 0.5, 0, 1, 43},
  {"4r", "RELEASE", 0, 0, 2.0, 44},
  // ENV MOD
  {"pitch_env", "PITCH", 0, 0, 1, 45},
  {"cutoff_env", "CUTOFF", 0, 0, 1, 46},
  {"duty_env", "PWM", 0, 0, 1, 47},
  {"", "", 0, 0, 1, 0},
  // LFO MOD
  {"lfo_1_freq", "LFO RATE", 1, 0.01, 8.0, 28},
  {"pitch_lfo", "PITCH", 0, 0, 1, 0},
  {"cutoff_lfo", "CUTOFF", 0, 0, 1, 48},
  {"duty_lfo", "PWM", 0, 0, 1, 0},
  // CHORUS
  /*{16, 4, "", "RATE", 0, 0, 1, 0},
  {17, 4, "", "DEPTH", 0, 0, 1, 0},
  {18, 4, "", "", 0, 0},
  {19, 4, "", "", 0, 0}*/
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
  {1, BUTTON_MODE_NOTE, "", 46},
};

// mode; param1[16]; min; max;
const LedsMapping LEDS_MAPPING[MENU_PAGES_LENGTH] = {
  {0},
  {0}
};

const byte FG_COLOR[3] {
  0x00, 0x00, 0xFF
};

#endif

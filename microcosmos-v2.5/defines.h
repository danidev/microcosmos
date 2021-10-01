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

#ifndef __DEFINES__
#define __DEFINES__

#include <Arduino.h>

typedef void (*voidFuncPtr)(void);

// GENERAL
#define FPS 1000/30 //ms 30fps
#define DEBOUNCE_TIME 120      /**< time beetween interrupts */
#define ONE_SECOND 60000

// EEPROM ADDRESSES
#define EEPROM_STORAGE 1 // 1: use eeprom, 0: don't use eeprom (developing)
#define EEPROM_PROGRAM_START 32
#define EEPROM_VERSION 8
#define EEPROM_VOLUME 9
#define EEPROM_MIDI_IN 10

// ANALOG POTS
#define EMA_ALPHA 0.2
#define MIN_ANALOG_VALUE 0
#define MAX_ANALOG_VALUE 1024

// BUTTON/GATE STATES
#define BUTTON_IDLE 0
#define BUTTON_PRESSED 1
#define BUTTON_RELEASED 2

// MICROCOSMOS V2 DEFINES
#define MICROCOSMOS

#define PWREN 29 // power pin

#define ADDRESS_CORE_LEDS 0x34
#define ADDRESS_TOP_LEDS 0x60
#define ADDRESS_ENCODERS 0x20
#define ADDRESS_BUTTONS 0x22
#define INTERRUPT_BUTTONS_PIN 4
#define INTERRUPT_ENCODERS_PIN 3

#define TFT_CS        	36
#define TFT_RST       	38 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC        	39
#define TFT_BLK        	40 // BACKLIGHT DISPLAY CONTROL ( 1= ON  0=OFF)

#define ENCODERS 5
#define BUTTONS 5
#define LEDS_COUNT 16
#define LEDS_BRIGHTNESS 0x20

const uint8_t ENCODER_LEDS[ENCODERS][3] = {
  {9,7,5},
  {19,17,11},
  {29,23,21},
  {35,33,31},
  {41,39,37}
};

const uint8_t BUTTON_LEDS[BUTTONS] = {
  43, 49, 51, 53, 55
};

const uint8_t RGB_LEDS[LEDS_COUNT][3] = {
  {55,56,57},
  {37,38,39},
  {19,20,21},
  {1,2,3},
  {58,59,60},
  {40,41,42},
  {22,23,24},
  {4,5,6},
  {61,62,63},
  {43,44,45},
  {25,26,27},
  {7,8,9},
  {64,65,66},
  {46,47,48},
  {28,29,30},
  {10,11,12}
};

const uint8_t POWER_INDICATOR[3] = {67,68,69};

// MIDI
#define MIDI_SERIAL_SPEED 31250
// #define MIDI_NOTE_ENABLED 0
// #define MIDI_CC_ENABLED 0

#endif

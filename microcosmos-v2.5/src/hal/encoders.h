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

#ifndef __I2C_ENCODERS__
#define __I2C_ENCODERS__

#include <Arduino.h>
#include <Wire.h>
#include "../../defines.h"
#include "i2c.h"

typedef void (*callbackEncoderPointer)(byte, byte);

const uint16_t ENCODER_MAX = 127;

const int8_t ENCODER_STATES[16] = {
    // new pin2 | new	pin1 | old pin2 |	old pin1
    0,  // 0 0 0 0 -> 0
    +1, // 0 0 0 1 -> 1
    -1, // 0 0 1 0 -> 2
    +2, // 0 0 1 1 -> 3
    -1, // 0 1 0 0 -> 4
    0,  // 0 1 0 1 -> 5
    -2, // 0 1 1 0 -> 6
    +1, // 0 1 1 1 -> 7
    +1, // 1 0 0 0 -> 8
    -2, // 1 0 0 1 -> 9
    0,  // 1 0 1 0 -> 10
    -1, // 1 0 1 1 -> 11
    +2, // 1 1 0 0 -> 12
    -1, // 1 1 0 1 -> 13
    +1, // 1 1 1 0 -> 14
    0,  // 1 1 1 1 -> 15
};

struct Encoder {
  uint8_t index;
  uint8_t clkByte;
  uint8_t dtaByte;
  int value;
  int min;
  int max;
  bool dispatch;
  unsigned long last_click;
  int read;
};

extern uint16_t enc_currentReading;
extern uint16_t enc_lastReading;
extern bool enc_requestInterrupt;
extern callbackEncoderPointer onEncoderChangeCallback;
extern Encoder encoders[ENCODERS];

void enc_callback();
void enc_setup();
void enc_polling();
int enc_get_value(uint8_t index);
void enc_set_value(uint8_t index, int value);
void enc_set_range(uint8_t index, int min, int max);
void enc_set_on_change(callbackEncoderPointer callback);

#endif

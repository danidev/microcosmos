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

#ifndef __I2C_BUTTONS__
#define __I2C_BUTTONS__

#include <Arduino.h>
#include <Wire.h>
#include "../../defines.h"
#include "i2c.h"

typedef void (*callbackButtonPointer)(byte, bool);

struct Button {
  uint8_t index;
  uint8_t address;
  bool state;
  bool dispatch;
};

const uint8_t buttonAddress[10] = {
  0,1,2,3,4,    // encoders
  8,9,10,11,12  // buttons
};

extern uint16_t btn_currentReading;
extern uint16_t btn_lastReading;
extern bool btn_requestInterrupt;
extern callbackButtonPointer onButtonChangeCallback;

void btn_callback();
void btn_setup();
void btn_polling();
void btn_set_on_change(callbackButtonPointer callback);

#endif

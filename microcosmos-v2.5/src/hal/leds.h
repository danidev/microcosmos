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

#ifndef __I2C_LEDS__
#define __I2C_LEDS__

#include <Arduino.h>
#include <Wire.h>
#include "i2c.h"
#include "../../defines.h"

struct RgbLed {
  uint8_t currentR;
  uint8_t currentG;
  uint8_t currentB;
  uint8_t nextR;
  uint8_t nextG;
  uint8_t nextB;
};

struct MonoLed {
  uint8_t current;
  uint8_t next;
};

extern RgbLed leds_encoders[ENCODERS];
extern MonoLed leds_buttons[BUTTONS];
extern RgbLed leds_rgbLeds[LEDS_COUNT];

void leds_setup();
void leds_update();

void leds_reset();
void leds_reset_core(void);
void leds_reset_top(void);

void leds_set_button(uint8_t index, uint8_t value);
void leds_set_encoder(uint8_t index, uint8_t r, uint8_t g, uint8_t b);
void leds_set_power_indicator();
void leds_set_strip(uint8_t index, uint8_t r, uint8_t g, uint8_t b, bool clean);
void leds_set_strip_range(uint8_t min, uint8_t max, uint8_t r, uint8_t g, uint8_t b, bool clean);

void leds_write_button(uint8_t l, uint8_t value);
void leds_write_encoder(uint8_t l, uint8_t r, uint8_t g, uint8_t b);
void leds_write_power_indicator(uint8_t r, uint8_t g, uint8_t b);
void leds_write_strip(uint8_t index, uint8_t r, uint8_t g, uint8_t b);

#endif

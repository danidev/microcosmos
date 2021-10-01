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

#include "leds.h"

RgbLed leds_encoders[ENCODERS];
MonoLed leds_buttons[BUTTONS];
RgbLed leds_rgbLeds[LEDS_COUNT];

void leds_setup() {
  i2c_write_wire_1(ADDRESS_CORE_LEDS, I2C_IODIR_A, 0x00);
  i2c_write_wire_1(ADDRESS_CORE_LEDS, I2C_IODIR_B, 0x00);

  leds_reset();
}

void leds_update() {
  bool coreReset = false;

  for (uint8_t i = 0; i < ENCODERS; i++) {
    if (leds_encoders[i].currentR != leds_encoders[i].nextR ||
      leds_encoders[i].currentG != leds_encoders[i].nextG ||
      leds_encoders[i].currentB != leds_encoders[i].nextB
    ) {
      leds_encoders[i].currentR = leds_encoders[i].nextR;
      leds_encoders[i].currentG = leds_encoders[i].nextG;
      leds_encoders[i].currentB = leds_encoders[i].nextB;
      if (!coreReset) {
        leds_reset_core();
        coreReset = true;
      }

      leds_write_encoder(i, leds_encoders[i].currentR , leds_encoders[i].currentG, leds_encoders[i].currentB);
    }
  }

  for (uint8_t i = 0; i < BUTTONS; i++) {
    if (leds_buttons[i].current != leds_buttons[i].next) {
      leds_buttons[i].current = leds_buttons[i].next;
      if (!coreReset) {
        leds_reset_core();
        coreReset = true;
      }
      leds_write_button(i, leds_buttons[i].current);
    }
  }

  if (coreReset) {
    i2c_write_wire_1(ADDRESS_CORE_LEDS, 0x49, 0x00);
  }

  bool topReset = false;

  for (uint8_t i = 0; i < LEDS_COUNT; i++) {
    if (leds_rgbLeds[i].currentR != leds_rgbLeds[i].nextR ||
      leds_rgbLeds[i].currentG != leds_rgbLeds[i].nextG ||
      leds_rgbLeds[i].currentB != leds_rgbLeds[i].nextB
    ) {
      leds_rgbLeds[i].currentR = leds_rgbLeds[i].nextR;
      leds_rgbLeds[i].currentG = leds_rgbLeds[i].nextG;
      leds_rgbLeds[i].currentB = leds_rgbLeds[i].nextB;
      if (!topReset) {
        leds_reset_top();

        i2c_write_wire_0(ADDRESS_TOP_LEDS, 0xfe, 0xc5);
        i2c_write_wire_0(ADDRESS_TOP_LEDS, 0xfd, 0x00); //page 0
        topReset = true;
      }
      leds_write_strip(i, leds_rgbLeds[i].currentR , leds_rgbLeds[i].currentG, leds_rgbLeds[i].currentB);
    }
  }
}

void leds_reset() {
  uint8_t i;
  for (i = 0; i < ENCODERS; i++) {
    leds_encoders[i].currentR = 0;
    leds_encoders[i].currentG = 0;
    leds_encoders[i].currentB = 0;
    leds_encoders[i].nextR = 0;
    leds_encoders[i].nextG = 0;
    leds_encoders[i].nextB = 0;
  }

  for (i = 0; i < BUTTONS; i++) {
    leds_buttons[i].current = 0;
    leds_buttons[i].next = 0;
  }

  for (i = 0; i < LEDS_COUNT; i++) {
    leds_rgbLeds[i].currentR = 0;
    leds_rgbLeds[i].currentG = 0;
    leds_rgbLeds[i].currentB = 0;
    leds_rgbLeds[i].nextR = 0;
    leds_rgbLeds[i].nextG = 0;
    leds_rgbLeds[i].nextB = 0;
  }
}

void leds_reset_core(void) {
  uint8_t i = 0;
  for(i=0x4A;i<=0x6D;i++) {
    i2c_write_wire_1(ADDRESS_CORE_LEDS, i,0xFF);//write all scaling
  }

  i2c_write_wire_1(ADDRESS_CORE_LEDS, 0x6e,0xff);//GCC
  i2c_write_wire_1(ADDRESS_CORE_LEDS, 0x49,0x00);//update PWM & congtrol registers
  i2c_write_wire_1(ADDRESS_CORE_LEDS, 0x00,0x01);//normal operation
}

void leds_reset_top(void) {
  int i;

  /*for(i=0;i<0x48;i++) {
    i2c_write_wire_0(ADDRESS_TOP_LEDS, i,0);
  }*/

  i2c_write_wire_0(ADDRESS_TOP_LEDS, 0xfe,0xc5);
  i2c_write_wire_0(ADDRESS_TOP_LEDS, 0xfd,0x01);

  for(i=1;i<0x48;i++) {
    i2c_write_wire_0(ADDRESS_TOP_LEDS, i,0xff);
  }

  i2c_write_wire_0(ADDRESS_TOP_LEDS, 0x52,0x70);
  i2c_write_wire_0(ADDRESS_TOP_LEDS, 0x51,0xFF); //GCC
  i2c_write_wire_0(ADDRESS_TOP_LEDS, 0x50,0x01); //
}

void leds_set_button(uint8_t index, uint8_t value) {
  if (index >= BUTTONS) {
    return;
  }

  leds_buttons[index].next = value;
}

void leds_set_encoder(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
  if (index >= ENCODERS) {
    return;
  }

  leds_encoders[index].nextR = r;
  leds_encoders[index].nextG = g;
  leds_encoders[index].nextB = b;
}

void leds_set_power_indicator() {
  // TODO: OPTIMIZE IO OPERATION!
  leds_write_power_indicator(LEDS_BRIGHTNESS, LEDS_BRIGHTNESS, 0);
}

void leds_set_strip(uint8_t index, uint8_t r, uint8_t g, uint8_t b, bool clean) {
  if (index >= LEDS_COUNT) {
    return;
  }

  if (clean) {
    for (uint8_t i = 0; i < LEDS_COUNT; i++) {
      leds_set_strip(i, 0, 0, 0, false);
    }
  }

  leds_rgbLeds[index].nextR = r;
  leds_rgbLeds[index].nextG = g;
  leds_rgbLeds[index].nextB = b;
}

void leds_set_strip_range(uint8_t min, uint8_t max, uint8_t r, uint8_t g, uint8_t b, bool clean) {
  for (uint8_t i = 0; i < LEDS_COUNT; i++) {
    if (i >= min && i < max) {
      leds_set_strip(i, r, g, b, false);
    } else {
      if (clean) {
        leds_set_strip(i, 0, 0, 0, false);
      }
    }
  }
}

void leds_write_encoder(uint8_t l, uint8_t r, uint8_t g, uint8_t b) {
  i2c_write_wire_1(ADDRESS_CORE_LEDS, ENCODER_LEDS[l][0], b);
  i2c_write_wire_1(ADDRESS_CORE_LEDS, ENCODER_LEDS[l][1], g);
  i2c_write_wire_1(ADDRESS_CORE_LEDS, ENCODER_LEDS[l][2], r);
}

void leds_write_button(uint8_t l, uint8_t value) {
  i2c_write_wire_1(ADDRESS_CORE_LEDS, BUTTON_LEDS[l], value);
}

void leds_write_strip(uint8_t index, uint8_t r, uint8_t g, uint8_t b) {
  i2c_write_wire_0(ADDRESS_TOP_LEDS, RGB_LEDS[index][0], b);
  i2c_write_wire_0(ADDRESS_TOP_LEDS, RGB_LEDS[index][1], g);
  i2c_write_wire_0(ADDRESS_TOP_LEDS, RGB_LEDS[index][2], r);
}

void leds_write_power_indicator(uint8_t r, uint8_t g, uint8_t b) {
  i2c_write_wire_0(ADDRESS_TOP_LEDS, 0xfe, 0xc5);
  i2c_write_wire_0(ADDRESS_TOP_LEDS, 0xfd, 0x00); //page 0
  i2c_write_wire_0(ADDRESS_TOP_LEDS, POWER_INDICATOR[0], b);
  i2c_write_wire_0(ADDRESS_TOP_LEDS, POWER_INDICATOR[1], g);
  i2c_write_wire_0(ADDRESS_TOP_LEDS, POWER_INDICATOR[2], r);
}

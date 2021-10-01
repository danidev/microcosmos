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

#include "buttons.h"

uint16_t btn_currentReading;
uint16_t btn_lastReading;
bool btn_requestInterrupt;
callbackButtonPointer onButtonChangeCallback = NULL;

void btn_callback() {
  btn_requestInterrupt = true;
}

void btn_setup() {
  btn_currentReading = 0;
  btn_lastReading = 0;
  btn_requestInterrupt = false;

  i2c_write_on_both_channels(ADDRESS_BUTTONS, I2C_IOCON_A, 0b01100000); // mirror and seq op disabled
  i2c_write_on_both_channels(ADDRESS_BUTTONS, I2C_GPPU_A, 0x00); // no pullup
  i2c_write_on_both_channels(ADDRESS_BUTTONS, I2C_GPINTEN_A, 0xFF); // enable interrupt

  // read from interrupt capture ports to clear them
  i2c_read(ADDRESS_BUTTONS, I2C_INTCAP_A);
  i2c_read(ADDRESS_BUTTONS, I2C_INTCAP_B);

  // attach interrupt
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_BUTTONS_PIN), btn_callback, FALLING);
}

void btn_polling() {
  if (btn_requestInterrupt) {
    btn_requestInterrupt = false;

    uint8_t a = 0;
    uint8_t b = 0;

    if (i2c_read(ADDRESS_BUTTONS, I2C_INTF_A)) {
      a = i2c_read(ADDRESS_BUTTONS, I2C_INTCAP_A);
    }

    if (i2c_read(ADDRESS_BUTTONS, I2C_INTF_B)) {
      b = i2c_read(ADDRESS_BUTTONS, I2C_INTCAP_B);
    }

    btn_currentReading = a | (b << 8);

    if (btn_lastReading == btn_currentReading) {
      return;
    }

    for (uint8_t i = 0; i < 16; i++) {
      if ((btn_currentReading & (1 << i)) != (btn_lastReading & (1 << i))) {
        bool state = (btn_currentReading & (1 << i)) > 0;
        if (onButtonChangeCallback != NULL) {
          for (uint8_t j = 0; j < 10; j++) {
            if (i == buttonAddress[j]) {
              onButtonChangeCallback(j, state);
            }
          }
        }
      }
    }

    btn_lastReading = btn_currentReading;
  }
}

void btn_set_on_change(callbackButtonPointer callback) {
  onButtonChangeCallback = callback;
}

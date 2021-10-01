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

#include "encoders.h"

uint16_t enc_currentReading;
uint16_t enc_lastReading;
bool enc_requestInterrupt;
callbackEncoderPointer onEncoderChangeCallback = NULL;
Encoder encoders[ENCODERS] = {
  {0, 0, 1, 0, 0, ENCODER_MAX, false, 0, 0},
  {1, 2, 3, 0, 0, ENCODER_MAX, false, 0, 0},
  {2, 4, 5, 0, 0, ENCODER_MAX, false, 0, 0},
  {3, 6, 7, 0, 0, ENCODER_MAX, false, 0, 0},
  {4, 8, 9, 0, 0, ENCODER_MAX, false, 0, 0}
};

void enc_callback() {
  enc_requestInterrupt = true;
}

void enc_setup() {
	enc_currentReading = 0;
  enc_lastReading = 0;
  enc_requestInterrupt = false;

	i2c_write_on_both_channels(ADDRESS_ENCODERS, I2C_IOCON_A, 0b01100000); // mirror and seq op disabled
  i2c_write_on_both_channels(ADDRESS_ENCODERS, I2C_GPPU_A, 0xFF); // enable pullup
  i2c_write_on_both_channels(ADDRESS_ENCODERS, I2C_GPINTEN_A, 0xFF); // enable interrupt
	i2c_write_on_both_channels(ADDRESS_ENCODERS, I2C_IPOL_A, 0xFF); // invert polarity

	// read from interrupt capture ports to clear them
  i2c_read(ADDRESS_ENCODERS, I2C_INTCAP_A);
  i2c_read(ADDRESS_ENCODERS, I2C_INTCAP_B);

  // attach interrupt
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_ENCODERS_PIN), enc_callback, FALLING);
}

unsigned long elapsed = 0;

void enc_polling() {
	if (enc_requestInterrupt) {
    enc_requestInterrupt = false;
    unsigned long current = millis();

    // read from interrupt
		uint8_t a = 0;
		uint8_t b = 0;

		if (i2c_read(ADDRESS_ENCODERS, I2C_INTF_A)) {
			a = i2c_read(ADDRESS_ENCODERS, I2C_INTCAP_A);
		}

		if (i2c_read(ADDRESS_ENCODERS, I2C_INTF_B)) {
			b = i2c_read(ADDRESS_ENCODERS, I2C_INTCAP_B);
		}

		enc_currentReading = a | (b << 8);

		if (enc_lastReading == enc_currentReading) {
      return;
    }

    // debounce
    if (current - elapsed < DEBOUNCE_TIME) {
      return;
    }

    elapsed = current;

    // check encoders
		uint8_t newA, newB, oldA, oldB;
		int v;

		for (uint8_t i = 0; i < 5; i++) {
			Encoder *e = &encoders[i];
			newA = (enc_currentReading & (1 << e->clkByte)) > 0;
			newB = (enc_currentReading & (1 << e->dtaByte)) > 0;
			oldA = (enc_lastReading & (1 << e->clkByte)) > 0;
			oldB = (enc_lastReading & (1 << e->dtaByte)) > 0;

      // THIRD ATTEMPT
      if (newA != oldA || newB != oldB) {
				v = oldA | (oldB << 1) | (newA << 2) | (newB << 3);
        int newValue = e->value;

        unsigned long elapsed = current - e->last_click;
        int step = 400 / elapsed + 1;

        // skip: 1100 -> 12

        // avoid go in the wrong verse
        if (step > 1 && v != e->read) {
          v = e->read;
        }

        switch (v) {
          case 8: // CW: 1000 -> 8
            newValue += step;
            break;
          case 4: // CCW: 0100 -> 4
            newValue -= step;
            break;
        }

        if (newValue > ENCODER_MAX) newValue = ENCODER_MAX;
        if (newValue < 0) newValue = 0;

        if (newValue == e->value) {
          return;
        }

        e->value = newValue;
        e->last_click = current;
        e->read = v;

        // Serial.printf("%d [%d%d%d%d -> %d] step:%d (%d) %dms\n", e->index, newB, newA, oldB, oldA, v, step, newValue, elapsed);

        if(onEncoderChangeCallback != NULL) {
          // Serial.printf("-> %d %d\n", i, e->value);
          onEncoderChangeCallback(i, e->value);
        }
			}

      // SECOND ATTEMPT
      /*if (newA != oldA || newB != oldB) {
        if (newB == 0) {
          return;
        }

        Serial.printf("%d%d\n", newA, newB);

        if (newA == 1) {
          e->value = e->value - 1;
        } else {
          e->value = e->value + 1;
        }

        if (e->value > ENCODER_MAX) e->value = ENCODER_MAX;
        if (e->value < 0) e->value = 0;

        if(onEncoderChangeCallback != NULL) {
          // Serial.printf("-> %d %d\n", i, e->value);
          onEncoderChangeCallback(i, e->value);
        }
      }*/

      // FIRST ATTEMPT
			/*if (newA != oldA || newB != oldB) {
				v = oldA | (oldB << 1) | (newA << 2) | (newB << 3);

        Serial.printf("%d%d\n", newA, newB);

        // e->last_click = current;

        e->value = e->value + ENCODER_STATES[v];

        // if (e->value > ENCODER_MAX) e->value = ENCODER_MAX;
        // if (e->value < 0) e->value = 0;

        if(onEncoderChangeCallback != NULL) {
          // Serial.printf("-> %d %d\n", i, e->value);
          onEncoderChangeCallback(i, e->value);
        }
			}*/
		}
	}
}

int enc_get_value(uint8_t index) {
  return encoders[index].value;
	//return map(encoders[index].value, 0, ENCODER_MAX, encoders[index].min, encoders[index].max);
}

void enc_set_value(uint8_t index, int value) {
  //encoders[index].value = map(value, encoders[index].min, encoders[index].max, 0, ENCODER_MAX);
	encoders[index].value = value;
}

void enc_set_range(uint8_t index, int min, int max) {
  encoders[index].min = min;
	encoders[index].max = max;
}

void enc_set_on_change(callbackEncoderPointer callback) {
  onEncoderChangeCallback = callback;
}

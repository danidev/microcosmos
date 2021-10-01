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

#include "i2c.h"

void i2c_setup() {
  // setup I2C
  Wire.begin();
  Wire.setClock(I2C_SPEED); //I2C 400kHz
  Wire1.begin();
  Wire1.setClock(I2C_SPEED); //I2C 400kHz
}

void i2c_write_wire_0(byte I2Caddress, byte memAddr, byte memValue) {
  Wire.beginTransmission(I2Caddress);
  Wire.write(memAddr);
  Wire.write(memValue);
  Wire.endTransmission();
}

void i2c_write_wire_1(byte I2Caddress, byte memAddr, byte memValue) {
  Wire1.beginTransmission(I2Caddress);
  Wire1.write(memAddr);
  Wire1.write(memValue);
  Wire1.endTransmission();
}

void i2c_write_on_both_channels(byte I2Caddress, byte memAddr, byte memValue) {
  i2c_write_wire_0(I2Caddress, memAddr, memValue);
  i2c_write_wire_0(I2Caddress, memAddr + 1, memValue);
}

// read a byte from the expander
unsigned int i2c_read(int I2Caddress, const byte reg) {
  Wire.beginTransmission(I2Caddress);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(I2Caddress, 1);
  return Wire.read();
}

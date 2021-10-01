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

#ifndef __I2C_WRAPPER__
#define __I2C_WRAPPER__

#include <Arduino.h>
#include <Wire.h>

#define I2C_SPEED 400000

//https://github.com/blemasle/arduino-mcp23017/blob/master/src/MCP23017.h
#define I2C_IODIR_A   0x00 // Controls the direction of the data I/O for port A.
#define I2C_IODIR_B   0x01 // Controls the direction of the data I/O for port B.
#define I2C_IPOL_A    0x02 // Configures the polarity on the corresponding GPIO_ port bits for port A.
#define I2C_IPOL_B    0x03 // Configures the polarity on the corresponding GPIO_ port bits for port B.
#define I2C_GPINTEN_A 0x04 // Controls the interrupt-on-change for each pin of port A.
#define I2C_GPINTEN_B 0x05 // Controls the interrupt-on-change for each pin of port B.
#define I2C_DEFVAL_A  0x06 // Controls the default comparaison value for interrupt-on-change for port A.
#define I2C_DEFVAL_B  0x07 // Controls the default comparaison value for interrupt-on-change for port B.
#define I2C_INTCON_A  0x08 // Controls how the associated pin value is compared for the interrupt-on-change for port A.
#define I2C_INTCON_B  0x09 // Controls how the associated pin value is compared for the interrupt-on-change for port B.
#define I2C_IOCON_A   0x0A // Controls the device.
#define I2C_IOCON_B   0x0B // Controls the device. MISSING ON THE LIBRARY!!!!!!!!!
#define I2C_GPPU_A    0x0C // Controls the pull-up resistors for the port A pins.
#define I2C_GPPU_B    0x0D // Controls the pull-up resistors for the port B pins.
#define I2C_INTF_A    0x0E // Reflects the interrupt condition on the port A pins.
#define I2C_INTF_B    0x0F // Reflects the interrupt condition on the port B pins.
#define I2C_INTCAP_A  0x10 // Captures the port A value at the time the interrupt occured.
#define I2C_INTCAP_B  0x11 // Captures the port B value at the time the interrupt occured.
#define I2C_GPIO_A    0x12 // Reflects the value on the port A.
#define I2C_GPIO_B    0x13 // Reflects the value on the port B.
#define I2C_OLAT_A    0x14 // Provides access to the port A output latches.
#define I2C_OLAT_B    0x15 // Provides access to the port B output latches.

void i2c_setup();
void i2c_write_wire_0(byte I2Caddress, byte memAddr, byte memValue);
void i2c_write_wire_1(byte I2Caddress, byte memAddr, byte memValue);
void i2c_write_on_both_channels(byte I2Caddress, byte memAddr, byte memValue);
unsigned int i2c_read(int I2Caddress, const byte reg);

#endif

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

#ifndef __STORAGE__
#define __STORAGE__

#include <Arduino.h>
#include <SD.h>
#include <EEPROM.h>
#include "../../defines.h"

#define STORAGE_MAX_FILES 64
#define STORAGE_NAME_LENGTH 16

extern bool storage_sd_available;
extern char storage_files[STORAGE_MAX_FILES][STORAGE_NAME_LENGTH];
extern uint8_t storage_count;

void storage_sd_setup(uint8_t csPin);
void storage_sd_list();
File storage_sd_open_file(const char * fileName, byte mode);
bool storage_sd_remove_file(const char * fileName);

void storage_eeprom_write(int address, uint8_t value);
uint8_t storage_eeprom_read(int address);
void storage_eeprom_clear();

#endif

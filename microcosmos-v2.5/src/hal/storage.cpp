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

#include "storage.h"

bool storage_sd_available = false;
char storage_files[STORAGE_MAX_FILES][STORAGE_NAME_LENGTH];
uint8_t storage_count;

void storage_sd_setup(uint8_t csPin) {
  // SD CARD INITIALIZATION
  if (!SD.begin(csPin)) {
    storage_sd_available = false;
  } else {
    storage_sd_available = true;
  }
}

void storage_sd_list() {
  if (!storage_sd_available) {
    return;
  }

  File dir = SD.open("/");
  storage_count = 0;

  while (true) {
    File entry = dir.openNextFile();

    if (!entry) {
      // no more storage_files
      break;
    }

    //Serial.print(entry.name());

    if (!entry.isDirectory()) {
      if (storage_count < STORAGE_MAX_FILES) {
        strcpy(storage_files[storage_count], entry.name());
        storage_count ++;
      }
    } else {
      // recursive not implemented
    }

    entry.close();
  }
}

File storage_sd_open_file(const char * fileName, byte mode) {
	if (storage_sd_available) {
		return SD.open(fileName, mode);
	} else {
		return File();
	}
}

bool storage_sd_remove_file(const char * fileName) {
	if (storage_sd_available) {
		return SD.remove(fileName);
	} else {
		return false;
	}
}

void storage_eeprom_write(int address, uint8_t value) {
  EEPROM.put(address, value);
}

uint8_t storage_eeprom_read(int address) {
  uint8_t value = EEPROM.read(address);
  return value;
}

void storage_eeprom_clear() {
  for (int i = 0; i < 1024; i++) {
    storage_eeprom_write(i, 255);
  }
}

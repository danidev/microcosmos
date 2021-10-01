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
#ifndef __BUTTON_MAPPING__
#define __BUTTON_MAPPING__

#define BUTTON_TYPE_DISABLED 0
#define BUTTON_TYPE_MOMENTARY 1
#define BUTTON_TYPE_TOGGLE 2

#define BUTTON_MODE_MENU_UP 1
#define BUTTON_MODE_MENU_DOWN 2
#define BUTTON_MODE_SINGLE 3
#define BUTTON_MODE_NOTE 4

#define BUTTON_MIDI_MODE_OFF 0
#define BUTTON_MIDI_MODE_NOTE 1
#define BUTTON_MIDI_MODE_CC 2

struct ButtonMapping {
<<<<<<< HEAD
  byte type;
  byte mode;
  char param[16];
=======
  uint8_t type;
  uint8_t mode;
  char param1[16];
  char param2[16];
  byte param1PressedValue;
  byte param2PressedValue;
  byte param1ReleasedValue;
  byte param2ReleasedValue;
>>>>>>> d50df7ed7718cca38ea4a6abf86687bb0ea44123
  byte midiNote;
  byte midiCC;
};

#endif

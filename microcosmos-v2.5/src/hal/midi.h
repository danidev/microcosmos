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

#ifndef __SERIAL_MIDI__
#define __SERIAL_MIDI__

#include <Arduino.h>
#include "../../defines.h"

// https://www.midi.org/specifications-old/item/table-1-summary-of-midi-message
#define MIDI_MSG_CC 0b10110000       // 176
#define MIDI_MSG_NOTE_ON 0b10010000  // 144
#define MIDI_MSG_NOTE_OFF 0b10000000 // 128
#define MIDI_MSG_SYSEX 0b11110000    // 240

// https://www.cs.cmu.edu/~music/cmsip/readings/MIDI%20tutorial%20for%20programmers.html
#define STATE_READY 0
#define STATE_CMD_RECEIVED 1
#define STATE_DATA_1_RECEIVED 2
#define STATE_DATA_2_RECEIVED 3

// MIDI OVER USB
// https://github.com/arduino/ArduinoCore-sam/blob/master/cores/arduino/USB/USBCore.cpp

struct MidiBuffer {
  byte cmd;
  byte channel;
  byte data1;
  byte data2;
  byte state;
};

typedef void (*callbackPointer)(byte, byte, byte);

extern MidiBuffer midi_buffer;
extern bool midi_setup_ok;

void midi_setup(int speed);
void midi_polling();
void midi_execute_callback();
void midi_set_note_on_callback(callbackPointer callback);
void midi_set_note_off_callback(callbackPointer callback);
void midi_set_control_change_callback(callbackPointer callback);

#endif

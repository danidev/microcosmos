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

#include "midi.h"

MidiBuffer midi_buffer = {0,0,0,0,5};
bool midi_setup_ok;

callbackPointer onNoteOnCallback = NULL;
callbackPointer onNoteOffCallback = NULL;
callbackPointer onControlChangeCallback = NULL;

void midi_setup(int speed) {
  Serial1.begin(speed);
  midi_setup_ok = true;
}

void midi_polling() {
  if (!midi_setup_ok) return;

  if (Serial1.available() == 0) {
    return;
  }

  byte r = Serial1.read();

  if ((r & (1 << 7)) > 0) {
    // status byte (1xxx xxxx)
    // message type is first 4 bits
    midi_buffer.cmd = r & 0b11110000;
    // channel is last 4 bits
    midi_buffer.channel = r & 0b00001111;

    midi_buffer.state = STATE_CMD_RECEIVED;
  } else {
    // data byte (0xxx xxxx)
    switch (midi_buffer.state) {
      case STATE_CMD_RECEIVED:
        midi_buffer.data1 = r;
        midi_buffer.state = STATE_DATA_1_RECEIVED;
        break;
      case STATE_DATA_1_RECEIVED:
        midi_buffer.data2 = r;
        midi_buffer.state = STATE_CMD_RECEIVED;
        midi_execute_callback();
        break;
      case STATE_DATA_2_RECEIVED:
        // this should neve happen...

        break;
    }
  }
}

void midi_execute_callback() {
  // Serial.printf("%d %d %d %d\n", midi_buffer.cmd, midi_buffer.channel, midi_buffer.data1, midi_buffer.data2);

  switch (midi_buffer.cmd) {
    case MIDI_MSG_CC:
      if (onControlChangeCallback != NULL) {
        onControlChangeCallback(midi_buffer.channel, midi_buffer.data1, midi_buffer.data2);
      }
      break;
    case MIDI_MSG_NOTE_ON:
      if (onNoteOnCallback != NULL) {
        onNoteOnCallback(midi_buffer.channel, midi_buffer.data1, midi_buffer.data2);
      }
      break;
    case MIDI_MSG_NOTE_OFF:
      if (onNoteOffCallback != NULL) {
        onNoteOffCallback(midi_buffer.channel, midi_buffer.data1, 0);
      }
      break;
  }
}

void midi_set_note_on_callback(callbackPointer callback) {
  onNoteOnCallback = callback;
}

void midi_set_note_off_callback(callbackPointer callback) {
  onNoteOffCallback = callback;
}

void midi_set_control_change_callback(callbackPointer callback) {
  onControlChangeCallback = callback;
}

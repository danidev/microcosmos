#define PWREN 29

#include <Arduino.h>
#include <Audio.h>
#include <USBHost_t36.h>
#include <Wire.h>

#include "audio.h"

#include "src/hal/i2c.h"
#include "src/hal/midi.h"
#include "src/hal/storage.h"

#include "src/hal/buttons.h"
#include "src/hal/display.h"
#include "src/hal/encoders.h"
#include "src/hal/leds.h"

#include "src/programs/boot.h"
#include "src/programs/dsp.h"

#include "src/dsp/mapping.h"

/**
  This is a fix for fprintf used by FAUST exported code to not crash the Board
*/
#include <cstdio>

auto &debugOut = Serial;

extern "C" {
int _write(int fd, const char *buf, int len) {
  // Send both stdout and stderr to debugOut
  if (fd == stdout->_file || fd == stderr->_file) {
    return debugOut.write(reinterpret_cast<const uint8_t *>(buf), len);
  }

  // Doing the following keeps this compatible with Print.cpp's requirements
  Print *p = reinterpret_cast<Print *>(fd);
  return p->write(reinterpret_cast<const uint8_t *>(buf), len);
}
}
/**
  End fix
*/

USBHost usbHost;
MIDIDevice midi1(usbHost);

uint8_t program;            /**< current running program */
unsigned long last_update;  /**< last update of the loop function (milliseconds) */

void setup() {
  // hardware initialization

  // power-up the board
  pinMode(PWREN, OUTPUT);
  digitalWrite(PWREN, HIGH);

  audio_setup();

  // IO setup
  i2c_setup();
  // midi_setup(MIDI_SERIAL_SPEED);
  usbHost.begin();

  Serial.begin(9600);

  if (MIDI_NOTE_ENABLED) {
    midi1.setHandleNoteOff(onNoteOff);
    midi1.setHandleNoteOn(onNoteOn);
    // midi_set_note_on_callback(onNoteOn);
    // midi_set_note_off_callback(onNoteOff);
  }

  if (MIDI_CC_ENABLED) {
    midi1.setHandleControlChange(onControlChange);
    // midi_set_control_change_callback(onControlChange);
  }

  // board initialization
  display_setup();
  display_set_fg_color(FG_COLOR[0], FG_COLOR[1], FG_COLOR[2]);
  display_draw_page_background();

  enc_setup();
  enc_set_on_change(onEncoderChange);

  btn_setup();
  btn_set_on_change(onButtonChange);

  leds_setup();
  leds_set_power_indicator();

  // programs initialization
  program = 0;
  last_update = millis();

  boot_setup();
  dsp_setup();

  delay(500);
}

void loop() {
  // midi_polling();
  usbHost.Task();
  midi1.read();

  enc_polling();
  btn_polling();

  unsigned long current = millis();
  if (current - last_update > FPS) {
    last_update = current;

    switch (program) {
      case 0:
        boot_loop(current, program);
        break;
      case 1:
        dsp_loop(current, program);
        break;
    }

    leds_update();
  }
}

void onNoteOn(byte channel, byte note, byte velocity) {
  // Serial.printf("note on %d %d %d\n", channel, note, velocity);
  switch (program) {
    case 0:
      break;
    case 1:
      dsp_on_note_on(channel, note, velocity);
      break;
  }
}

void onNoteOff(byte channel, byte note, byte velocity) {
  switch (program) {
    case 0:
      break;
    case 1:
      dsp_on_note_off(channel, note, velocity);
      break;
  }
}

void onControlChange(byte channel, byte control, byte value) {
  switch (program) {
    case 0:
      break;
    case 1:
      dsp_on_cc(channel, control, value);
      break;
  }
}

void onEncoderChange(uint8_t index, uint8_t value) {
  switch (program) {
    case 0:
      break;
    case 1:
      dsp_on_enc_change(index, value);
      break;
  }
}

void onButtonChange(uint8_t index, bool pressed) {
  switch (program) {
    case 0:
      break;
    case 1:
      dsp_on_btn_change(index, pressed);
      break;
  }
}

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

#ifndef __TFT_DISPLAY__
#define __TFT_DISPLAY__

#include <Arduino.h>
#include <Adafruit_ST7789.h>
// https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_SPITFT.h

#include "../../defines.h"

#define FONT_WIDTH 6
#define LINE_HEIGHT 12
#define ENTRIES_COUNT 9

const bool DISABLED = false;

struct Entry {
  char label[16];
  int value;
  uint8_t y;
  uint16_t fgColor;
  uint16_t bgColor;
  bool changed;
};

extern Adafruit_ST7789 display_tft;
extern word display_bg_color;
extern word display_fg_color;
extern word display_clr_color;
extern uint8_t display_scale;
extern uint8_t display_line_height;
extern uint8_t display_x_offset;
extern uint8_t display_y_offset;
extern uint8_t display_width;
extern uint8_t display_height;
extern uint8_t display_x_clr_val;
extern Entry display_entries[ENTRIES_COUNT];

void display_setup();

void display_clear_screen();
void display_clear_line(uint8_t line);

void display_draw_page_background();
void display_draw_param_line(uint8_t line, const char *name, int value);
void display_draw_string_line(uint8_t line, const char *text);

word display_convert_rgb(byte r, byte g, byte b);

void display_set_fg_color(byte r, byte g, byte b);

#endif

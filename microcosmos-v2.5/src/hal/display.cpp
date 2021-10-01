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

#include "display.h"

Adafruit_ST7789 display_tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
word display_bg_color;
word display_fg_color;
word display_clr_color;
uint8_t display_scale;
uint8_t display_line_height;
uint8_t display_x_offset;
uint8_t display_y_offset;
uint8_t display_width;
uint8_t display_height;
uint8_t display_x_clr_val;
Entry display_entries[ENTRIES_COUNT];

void display_setup() {

  pinMode(TFT_BLK, OUTPUT);
  digitalWrite(TFT_BLK, HIGH);
  display_tft.init(240, 240, SPI_MODE0);
  display_tft.setRotation(3);

  display_scale = 3;
  display_x_offset = 18;
  display_y_offset = 7;
  display_line_height = display_scale * LINE_HEIGHT;
  display_width = display_tft.width();
  display_height = display_tft.height();
  display_x_clr_val = display_width - (FONT_WIDTH * display_scale * 3);
  display_bg_color = display_convert_rgb(0x00, 0x00, 0x00);
  display_fg_color = display_convert_rgb(0xFF, 0xFF, 0xFF);
  display_clr_color = display_convert_rgb(0xFF, 0x00, 0x00);

  display_tft.setTextSize(display_scale);

  display_clear_screen();
}

void display_clear_screen() {
  for(uint8_t i = 0; i < ENTRIES_COUNT; i++) {
    strcpy(display_entries[i].label, "");
    display_entries[i].value = -1;
    display_entries[i].y = i * display_line_height;

    if (i == 0 || i == 5) {
      display_entries[i].bgColor = display_fg_color;
      display_entries[i].fgColor = display_bg_color;
    } else {
      display_entries[i].bgColor = display_bg_color;
      display_entries[i].fgColor = display_fg_color;
    }

    display_entries[i].changed = false;
  }

  display_tft.fillRect(0, 0, 240, 240, display_bg_color);
}

void display_clear_line(uint8_t line) {
  strcpy(display_entries[line].label, "");
  display_entries[line].value = -1;

  if (!DISABLED) {
    display_tft.fillRect(0, display_entries[line].y, (FONT_WIDTH * display_scale * 10), display_line_height, display_entries[line].bgColor);
    display_tft.fillRect(display_x_clr_val, display_entries[line].y, display_width, display_line_height, display_entries[line].bgColor);
  }
}

void display_draw_page_background() {
  display_tft.fillRect(0, 0, display_width, display_line_height, display_fg_color);
  display_tft.fillRect(0, display_line_height, display_width, display_line_height * 5, display_bg_color);
  display_tft.fillRect(0, display_line_height * 5, display_width, display_line_height, display_fg_color);

  int p =  display_width - (FONT_WIDTH * display_scale * 3) - 5;
  int bottom = display_line_height * 5 + display_y_offset;
  display_tft.fillRect(p, 0, 1, bottom, display_fg_color);
}

void display_draw_param_line(uint8_t line, const char *name, int value) {
  if (line > ENTRIES_COUNT-1) {
    return;
  }

  bool sameValue = false;
  bool sameLabel = false;

  if (strcmp(display_entries[line].label,name) == 0) {
    sameLabel = true;
  } else {
    strcpy(display_entries[line].label, name);
  }

  if (display_entries[line].value == value) {
    sameValue = true;
  } else {
    display_entries[line].value = value;
  }

  if (sameValue && sameLabel) {
    return;
  }

  int fw = (FONT_WIDTH * display_scale);
  if (value > 9 && value < 100) {
    fw *= 2;
  } else if (value >= 100 && value < 1000) {
    fw *= 3;
  } else if (value >= 1000 && value < 10000) {
    fw *= 4;
  } else if (value >= 10000 && value < 100000) {
    fw *= 5;
  } else if (value >= 100000 && value < 1000000) {
    fw *= 5;
  } else if (value < 0 && value > -10) {
    fw *= 2;
  } else if (value <= -10 && value > -100) {
    fw *= 3;
  } else if (value <= -100 && value > -1000) {
    fw *= 4;
  } else if (value <= -1000 && value > -10000) {
    fw *= 5;
  } else if (value <= -10000 && value > -100000) {
    fw *= 6;
  }

  if (!DISABLED) {
    display_tft.setTextColor(display_entries[line].fgColor);

    if(!sameLabel) {
      display_tft.fillRect(0, display_entries[line].y, (FONT_WIDTH * display_scale * 10), display_line_height, display_entries[line].bgColor);
      display_tft.setCursor(display_x_offset, display_entries[line].y + display_y_offset);
      display_tft.println(name);
    }

    if (!sameValue) {
      display_tft.fillRect(display_x_clr_val, display_entries[line].y, display_width, display_line_height, display_entries[line].bgColor);
      display_tft.setTextSize(display_scale);
      display_tft.setCursor(display_width - fw, display_entries[line].y + display_y_offset);
      display_tft.println(value);
    }
  }
}

void display_draw_string_line(uint8_t line, const char *text) {
  if (line > ENTRIES_COUNT-1) {
    return;
  }

  if (strcmp(display_entries[line].label, text) == 0) {
    return;
  } else {
    strcpy(display_entries[line].label, text);
  }

  display_entries[line].value = -1;

  if (!DISABLED) {
    display_tft.setTextColor(display_entries[line].fgColor);
    display_tft.fillRect(0, display_entries[line].y, display_width, display_line_height, display_entries[line].bgColor);
    display_tft.setCursor(display_x_offset, display_entries[line].y + display_y_offset);
    display_tft.println(display_entries[line].label);
  }
}

word display_convert_rgb(byte r, byte g, byte b) {
  return ( ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3) );
}

void display_set_fg_color(byte r, byte g, byte b) {
  display_fg_color = display_convert_rgb(r, g, b);

  for(byte i = 0; i < ENTRIES_COUNT; i++) {

    if (i == 0 || i == 5) {
      display_entries[i].bgColor = display_fg_color;
      display_entries[i].fgColor = display_bg_color;
    } else {
      display_entries[i].bgColor = display_bg_color;
      display_entries[i].fgColor = display_fg_color;
    }

    display_entries[i].changed = false;
  }
}

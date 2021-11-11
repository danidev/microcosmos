#include "dsp.h"

MenuParam dsp_menu_params[MENU_PARAMS_LENGTH];
byte dsp_page = 0;
byte lastNote = 0;

byte buttonStates[BUTTONS_MAPPING_LENGHT];

void dsp_setup() {
  persistence_setup(DSP);

  // menu items initialization
  byte i, eepromValue;
  float value;
  for (byte page = 0; page < MENU_PAGES_LENGTH; page++) {
    for (byte param = 0; param < PARAMS_PER_PAGE; param++) {
      i = param + (page * PARAMS_PER_PAGE);
      dsp_menu_params[i].address = i;
      dsp_menu_params[i].page = page;

      if (strlen(MENU_PARAMS[i].param) > 0) {
        strcpy(dsp_menu_params[i].param, MENU_PARAMS[i].param);
        strcpy(dsp_menu_params[i].display, MENU_PARAMS[i].display);
        dsp_menu_params[i].controller = MENU_PARAMS[i].controller;
        dsp_menu_params[i].min = MENU_PARAMS[i].min;
        dsp_menu_params[i].max = MENU_PARAMS[i].max;

        eepromValue = storage_eeprom_read(i + EEPROM_PROGRAM_START);

        if (eepromValue > 127) {
          value = MENU_PARAMS[i].value;
        } else {
          value = dsp_encoder_to_param(&dsp_menu_params[i], eepromValue);
        }

        dsp_menu_params[i].value = value;
        audio_set_param(dsp_menu_params[i].param, dsp_menu_params[i].value);
      }
    }
  }
  // end menu items setup

  // main volume setup
  byte volume = storage_eeprom_read(EEPROM_VOLUME);
  if (volume > 127) {
    volume = 36;
    storage_eeprom_write(EEPROM_VOLUME, volume);
  }

  enc_set_value(0, volume);
  audio_set_main_volume(volume / 127.);
  // end main volume setup

  // reset button states
  for(byte i = 0; i< BUTTONS_MAPPING_LENGHT; i++) {
    buttonStates[i] = 0;
  }

  dsp_update_encoders();
}

// uint8_t l = 0;

void dsp_loop(unsigned long current, uint8_t &state) {

  if (LEDS_MAPPING[dsp_page].mode > 0) {
    float p = audio_get_param(LEDS_MAPPING[dsp_page].param1);
    byte f = (byte)map(
      p,
      LEDS_MAPPING[dsp_page].min,
      LEDS_MAPPING[dsp_page].max,
      0,
      16);

    if (f > 15) f = 15;

    switch (LEDS_MAPPING[dsp_page].mode) {
      case 1:
        leds_set_strip(f,
          LEDS_MAPPING[dsp_page].color[0],
          LEDS_MAPPING[dsp_page].color[1],
          LEDS_MAPPING[dsp_page].color[2],
          true);
        break;
      case 2:
        leds_set_strip_range(0,
          f,
          LEDS_MAPPING[dsp_page].color[0],
          LEDS_MAPPING[dsp_page].color[1],
          LEDS_MAPPING[dsp_page].color[2],
          true);
        break;
    }
  }

  display_draw_string_line(0, PAGE_TITLES[dsp_page]);
  display_draw_param_line(5, "VOLUME", enc_get_value(0));

  leds_set_encoder(0, LEDS_BRIGHTNESS, LEDS_BRIGHTNESS, 0);

  if (MENU_PAGES_LENGTH > 1) {
    leds_set_button(0, LEDS_BRIGHTNESS);
  } else {
    leds_set_button(0, 0);
  }

  byte param = 0;
  for (byte i=0; i<MENU_PARAMS_LENGTH; i++) {
    if (dsp_menu_params[i].page == dsp_page) {
      if (strlen(dsp_menu_params[i].param) > 0) {
        display_draw_param_line(param + 1, dsp_menu_params[i].display, dsp_param_to_encoder(&dsp_menu_params[i]));
        leds_set_encoder(param + 1, 0, LEDS_BRIGHTNESS, LEDS_BRIGHTNESS);
      } else {
        display_clear_line(param + 1);
        leds_set_encoder(param + 1, 0, 0, 0);
      }

      param ++;
    }
  }

  for (byte i = 6; i < 10; i++) {
    byte btnIndex = (BUTTONS_MAPPING_LENGHT > 10) ? i + (10 * dsp_page) : i;
    leds_set_button(i-5, buttonStates[btnIndex] ? LEDS_BRIGHTNESS : 0);
  }

  // leds_set_button(0, LEDS_BRIGHTNESS);
}

void dsp_on_note_on(byte channel, byte note, byte velocity) {
  // Check if note is mapped to a button
  bool found = false;
  for (byte i = 0; i < BUTTONS_MAPPING_LENGHT; i++) {
    if (BUTTONS_MAPPING[i].midiNote == note &&
      BUTTONS_MAPPING[i].mode == BUTTON_MODE_SINGLE) {
        audio_set_param(BUTTONS_MAPPING[i].param, 1);
        found = true;
        break;
      }
  }

  if (!MIDI_NOTE_ENABLED) {
    return;
  }

  // else is a normal gate/note midi message
  if (!found) {
    lastNote = note;
    audio_set_param("gate", true);
    audio_set_param("note", note);
  }
  //TODO MIDI visual feedback
}

void dsp_on_note_off(byte channel, byte note, byte velocity) {
  // Check if note is mapped to a button
  bool found = false;
  for (byte i = 0; i < BUTTONS_MAPPING_LENGHT; i++) {
    if (BUTTONS_MAPPING[i].midiNote == note &&
      BUTTONS_MAPPING[i].mode == BUTTON_MODE_SINGLE) {
        audio_set_param(BUTTONS_MAPPING[i].param, 0);
        found = true;
        break;
      }
  }

  if (!MIDI_NOTE_ENABLED) {
    return;
  }

  // else is a normal midi off message
  if (!found && lastNote == note) {
    audio_set_param("gate", false);
  }
}

void dsp_on_cc(byte channel, byte control, byte value) {
  if (!MIDI_CC_ENABLED) {
    return;
  }

  bool found = false;
  for (byte i=0; i<MENU_PARAMS_LENGTH; i++) {
    MenuParam *p = &dsp_menu_params[i];
    if (p->controller == control) {
      if (strlen(p->param) > 0) {
        dsp_page = p->page;
        p->value = dsp_encoder_to_param(p, value);
        audio_set_param(p->param, p->value);
        storage_eeprom_write(p->address + EEPROM_PROGRAM_START, value);
        found = true;
      }
    }
  }

  // TODO: must be optimized
  if (found) {
    dsp_update_encoders();
  }

  // Check if CC is mapped to a button
  for (byte i = 0; i < BUTTONS_MAPPING_LENGHT; i++) {
    if (BUTTONS_MAPPING[i].midiCC == control &&
      BUTTONS_MAPPING[i].mode == BUTTON_MODE_SINGLE) {
        audio_set_param(BUTTONS_MAPPING[i].param, value > 0);
        break;
      }
  }
}

void dsp_on_enc_change(uint8_t index, uint8_t value) {
  if (index == 0) {
    // first encoder is the main volume control
    audio_set_main_volume(value / 127.);
    storage_eeprom_write(EEPROM_VOLUME, value);
  } else {
    // change param

    MenuParam *p = dsp_get_page_param(index - 1);

    if (strlen(p->param) > 0) {
      p->value = dsp_encoder_to_param(p, value);
      audio_set_param(p->param, p->value);
      storage_eeprom_write(p->address + EEPROM_PROGRAM_START, value);
    }
  }
}

void dsp_on_btn_change(uint8_t index, bool pressed) {
  // BUTTON_MODE_DISABLED 0
  // BUTTON_MODE_MENU_UP 1
  // BUTTON_MODE_MENU_DOWN 2
  // BUTTON_MODE_SINGLE 3
  // BUTTON_MODE_DOUBLE 4

  byte i = (BUTTONS_MAPPING_LENGHT > 10) ? index + (10 * dsp_page) : index;

  if (BUTTONS_MAPPING[i].type == BUTTON_TYPE_DISABLED) {
    return;
  }

  switch (BUTTONS_MAPPING[i].mode) {
    case BUTTON_MODE_MENU_UP:
      if (pressed) {
        dsp_page = (dsp_page + 1) % MENU_PAGES_LENGTH;
        dsp_update_encoders();
      }
      break;
    case BUTTON_MODE_MENU_DOWN:
      if (pressed && dsp_page > 0) {
        dsp_page--;
        dsp_update_encoders();
      }
      break;
    case BUTTON_MODE_SINGLE:
      audio_set_param(BUTTONS_MAPPING[i].param, pressed);
      break;
    case BUTTON_MODE_NOTE:
      audio_set_param("gate", pressed);
      audio_set_param("note", BUTTONS_MAPPING[i].midiNote);
      break;
  }

  buttonStates[i] = (BUTTONS_MAPPING[i].type == BUTTON_TYPE_TOGGLE) ? (pressed ? !buttonStates[i]: buttonStates[i]) : pressed;
}

MenuParam* dsp_get_page_param(uint8_t num) {
  int i = num + (dsp_page * PARAMS_PER_PAGE);
  Serial.printf("num=%d i=%d dsp_page=%d\n", num, i, dsp_page);
  MenuParam* d = &dsp_menu_params[i];
  Serial.printf("%s\n", d->param);
  return d;
}

uint8_t dsp_param_to_encoder(MenuParam *menuParam) {
  uint8_t encoder_value = map(menuParam->value, menuParam->min, menuParam->max, 0, 127);
  return encoder_value;
}

float dsp_encoder_to_param(MenuParam *menuParam, uint8_t encoder_value) {
  float v = map((float)encoder_value, 0.0, 127.0, menuParam->min, menuParam->max);
  return v;
}

void dsp_update_encoders() {
  uint8_t param = 0;
  for (int i=0; i<MENU_PARAMS_LENGTH; i++) {
    if (strlen(dsp_menu_params[i].param) > 0) {
      if (dsp_menu_params[i].page == dsp_page) {
        if (param < MENU_PARAMS_LENGTH - 1) {
          enc_set_value(param + 1, dsp_param_to_encoder(&dsp_menu_params[i]));
        }
        param ++;
      }
    }
  }
}

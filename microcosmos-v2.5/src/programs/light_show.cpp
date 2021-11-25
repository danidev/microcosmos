#include "light_show.h"

byte ls_cycle;
unsigned long ls_last;
byte ls_next_state;


void lightshow_setup() {
  ls_cycle = 0;
  ls_last = 0;
  ls_next_state = 0;
}

void lightshow_loop(unsigned long current, byte &state) {
  if (current-ls_last >= 250) {
    ls_last = current;
  } else {
    return;
  }

  ls_cycle = (ls_cycle + 1) % 16;

  leds_set_strip(ls_cycle, LEDS_BRIGHTNESS, LEDS_BRIGHTNESS, 0, true);
  display_draw_string_line(0, "MICROCOSMOS");
  display_draw_param_line(1, DSP, VERSION);
  display_draw_param_line(2, "version", VERSION);

  for(byte i = 0; i < 5; i++) {
    leds_set_button(i, 0);
    leds_set_encoder(i, 0, 0, 0);
  }

  leds_set_button(ls_cycle % 5, LEDS_BRIGHTNESS);

  leds_set_encoder(4 - ls_cycle % 5, 0, 0, LEDS_BRIGHTNESS);

  if (ls_next_state > 0) {
    display_clear_lines();
    leds_set_strip(0, 0, 0, 0, true);
    state = ls_next_state;
  }
}

void lightshow_on_btn_change(byte index, bool pressed) {
  ls_next_state = 1;
}

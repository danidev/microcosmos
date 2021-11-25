#include "boot.h"

byte boot_cycle;
byte boot_next_state;

void boot_setup() {
  boot_cycle = 0;
  boot_next_state = 0;
}

void boot_loop(unsigned long current, byte &state) {
  boot_cycle = (boot_cycle + 1) % 32;

  leds_set_strip(boot_cycle % 16, LEDS_BRIGHTNESS, 0, 0, true);
  display_draw_string_line(0, "MICROCOSMOS");
  display_draw_param_line(1, DSP, VERSION);
  display_draw_param_line(2, "version", VERSION);
  display_draw_param_line(3, "BOOTING", boot_cycle);

  for(byte i = 0; i < 5; i++) {
    leds_set_button(i, 0);
  }

  leds_set_button(boot_cycle % 5, LEDS_BRIGHTNESS);

  if (boot_cycle == 0) {
    display_clear_lines();
    leds_set_strip(0, 0, 0, 0, true);
    if (boot_next_state > 0) {
      state = boot_next_state;
    } else {
      state ++;
    }
  }
}

void boot_on_btn_change(byte index, bool pressed) {
  boot_next_state = 2;
}

#include "boot.h"

uint8_t cycle;

void boot_setup() {
  cycle = 0;
}

void boot_loop(unsigned long current, uint8_t &state) {
  cycle = (cycle + 1) % 16;

  leds_set_strip(cycle, LEDS_BRIGHTNESS, 0, 0, true);
  display_draw_string_line(0, "MICROCOSMOS");
  display_draw_param_line(1, "BOOTING", cycle);

  for(byte i = 0; i < 5; i++) {
    leds_set_button(i, 0);
  }

  leds_set_button(cycle % 5, LEDS_BRIGHTNESS);

  if (cycle == 0) {
    state ++;
  }
}

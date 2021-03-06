/**
 * Boot program
 * It does a fast light show then switch the state to the next program
 */
#ifndef __BOOT__
#define __BOOT__

#include "../dsp/mapping.h"
#include "../hal/leds.h"
#include "../hal/display.h"
#include "../../defines.h"

/**
 * setup function must be called on the main .ino setup
 */
void boot_setup();

/**
 * update function must be called on the main .ino loop
 * @param current current timestamp in milliseconds
 * @param state the main .ino state (can be used as program index)
 */
void boot_loop(unsigned long current, byte &state);

void boot_on_btn_change(byte index, bool pressed);

#endif

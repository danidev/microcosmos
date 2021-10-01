/**
 * Boot program
 * It does a fast light show then switch the state to the next program
 */
#ifndef __BOOT__
#define __BOOT__

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
void boot_loop(unsigned long current, uint8_t &state);

#endif

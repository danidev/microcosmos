/**
 * Boot program
 * It does a fast light show then switch the state to the next program
 */
#ifndef __LIGTH_SHOW__
#define __LIGTH_SHOW__

#include "../dsp/mapping.h"
#include "../hal/leds.h"
#include "../hal/display.h"
#include "../../defines.h"

/**
 * setup function must be called on the main .ino setup
 */
void lightshow_setup();

/**
 * update function must be called on the main .ino loop
 * @param current current timestamp in milliseconds
 * @param state the main .ino state (can be used as program index)
 */
void lightshow_loop(unsigned long current, byte &state);

void lightshow_on_btn_change(byte index, bool pressed);

#endif

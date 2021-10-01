/**
 * Boot program
 * It does a fast light show then switch the state to the next program
 */
#ifndef __MICROCOSMOS_DSP_PROGRAM__
#define __MICROCOSMOS_DSP_PROGRAM__

#include "../core/persistence.h"
#include "../dsp/mapping.h"
#include "../hal/display.h"
#include "../hal/encoders.h"
#include "../hal/leds.h"
#include "../hal/storage.h"
#include "../../defines.h"
#include "../../audio.h"

/**
 * setup function must be called on the main .ino setup
 */
void dsp_setup();

/**
 * update function must be called on the main .ino loop
 * @param current current timestamp in milliseconds
 * @param state the main .ino state (can be used as program index)
 */
void dsp_loop(unsigned long current, uint8_t &state);

void dsp_on_note_on(byte channel, byte note, byte velocity);
void dsp_on_note_off(byte channel, byte note, byte velocity);
void dsp_on_cc(byte channel, byte control, byte value);
void dsp_on_enc_change(uint8_t index, uint8_t value);
void dsp_on_btn_change(uint8_t index, bool pressed);

MenuParam* dsp_get_page_param(uint8_t num);
uint8_t dsp_param_to_encoder(MenuParam *menuParam);
float dsp_encoder_to_param(MenuParam *menuParam, uint8_t encoder_value);

void dsp_update_encoders();

#endif

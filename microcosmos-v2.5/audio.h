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

#ifndef __AUDIO_DSP__
#define __AUDIO_DSP__

#include "defines.h"
#include <Audio.h>
#include "src/dsp/MicrocosmosDsp/MicrocosmosDsp.h"

void audio_setup();
void audio_set_param(const char *path, float value);
float audio_get_param(const char *path);
void audio_set_main_volume(float value);

#endif
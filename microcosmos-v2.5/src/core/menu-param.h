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

#ifndef __MENU_PARAM__
#define __MENU_PARAM__

// MENU PARAMETER STRUCTURE
struct MenuParam {
  char param[16];             // faust param name
  char display[16];           // displayed param name
  float value;                // (default) value of the parameter
  float min;                  // min value for the param
  float max;                  // max value for the param
  byte controller;            // CC mapping
  byte address;            // id of the parameter (for direct access)
  byte page;               // page where the parameter is displayed
};

#endif

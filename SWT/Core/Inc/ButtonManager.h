/*
 * ButtonManager.h
 *
 *  Created on: Nov 01, 2025
 *      Author: Ch-Tima
 * SWT
 * Copyright (C) 2025  <Ch-Tima>
 *
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <stdint.h>
#include "main.h"
#include "stm32f103x6.h"

#define SHORT_CLICK 1
#define LONG_CLICK 35
#define HOLD_TICKS 75

typedef enum {
    BUTTON_NONE,
    BUTTON_SHORT,
    BUTTON_LONG,
    BUTTON_HOLD,
} ButtonStatus_t;

typedef enum{
    BUTTON_UP,
    BUTTON_DOWN
} ButtonID_t;

ButtonStatus_t Buttons_GetState(ButtonID_t btn_id);

#endif
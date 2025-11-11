/*
 * UI_SetTime.h
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
#ifndef UI_SETTIME_H
#define UI_SETTIME_H

#include "display.h"
#include "RTCManager.h"
#include "ButtonManager.h"
#include "main.h"
#include "Utils.h"
#include "UIManager.h"

void UI_Time_Init();
void UI_Time_Draw(ButtonStatus_t btnup_status, ButtonStatus_t btndown_status);

#endif
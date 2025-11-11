/*
 * UIManager.c
 *
 *  Created on: Oct 24, 2025
 *      Author: Ch-Tima
 * 
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
#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <stdint.h>
#include "display.h"
#include "Battery.h"
#include "Thermistor.h"
#include "RTCManager.h"
#include "ButtonManager.h"
#include "Utils.h"
#include "main.h"

//UI
#include "UI/UI_SetTime.h"

#define MAIN_VIEW 0xA
#define MENU_VIEW 0xB
#define UI_SET_TIME 0xB0
#define UI_SET_DATE 0xB1
#define UI_SETUP_BATTERY 0xB2
#define UI_SETUP_CLK 0xB3
#define UI_INFO 0xC

typedef struct {
    char *title;
    uint8_t menuId;
    uint8_t isSelect;
} MenuItem;

void UI_Init(void);
void UI_Update();
void UI_SetView(uint8_t id);
void UI_UpdateDataFromRTC();
void UI_UpdateDataFromADC();

#endif


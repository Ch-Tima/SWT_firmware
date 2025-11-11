/*
 * UI_SetTime.h
 *
 *  Created on: Nov 01, 2025
 *      Author: Ch-Tima
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
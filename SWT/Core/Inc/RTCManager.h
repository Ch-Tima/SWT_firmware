/*
 * RTCManager.h
 *
 *  Created on: Oct 20, 2025
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
#ifndef INC_RTCMANAGER_H_
#define INC_RTCMANAGER_H_

#include "stm32f1xx_hal.h"

void Get_Time_Now(char *timeStr, RTC_TimeTypeDef *clkTime);

void Get_Date_Now(char *dateStr, uint8_t format, RTC_DateTypeDef *clkTime);

void Update_RTCTime(uint8_t h, uint8_t m, uint8_t s);

#endif /* INC_RTCMANAGER_H_ */

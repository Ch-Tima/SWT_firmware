/*
 * RTCManager.c
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

#include "RTCManager.h"

extern RTC_HandleTypeDef hrtc;
extern  RTC_TimeTypeDef clkTime;
const static char *weekDays[7] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

void Get_Time_Now(char *timeStr, RTC_TimeTypeDef *clkTime){
		HAL_RTC_GetTime(&hrtc, clkTime, RTC_FORMAT_BIN);
		timeStr[0] = '0' + clkTime->Hours / 10;
		timeStr[1] = '0' + clkTime->Hours % 10;
		timeStr[2] = ':';
		timeStr[3] = '0' + clkTime->Minutes / 10;
		timeStr[4] = '0' + clkTime->Minutes % 10;
		timeStr[5] = ':';
		timeStr[6] = '0' + clkTime->Seconds / 10;
		timeStr[7] = '0' + clkTime->Seconds % 10;
		timeStr[8] = '\0';
}

void Get_Date_Now(char *dateStr, uint8_t format, RTC_DateTypeDef *clkDate){
	HAL_RTC_GetDate(&hrtc, clkDate, RTC_FORMAT_BIN);


		uint8_t pos = 0;
		if(format >> 0 & 1){
			const char *day = weekDays[clkDate->WeekDay];
	        for(uint8_t i = 0; i < 3; i++){
	        	dateStr[pos++] = day[i];
	        }
			dateStr[pos++] = ' ';
		}

		if(format >> 1 & 1){
			dateStr[pos++] = '0' + clkDate->Date / 10;
			dateStr[pos++] = '0' + clkDate->Date % 10;
			dateStr[pos++] = '.';
		}

		if(format >> 2 & 1){
			dateStr[pos++] = '0' + clkDate->Month / 10;
			dateStr[pos++] = '0' + clkDate->Month % 10;
			dateStr[pos++] = '.';
		}

		if(format >> 3 & 1){
			dateStr[pos++] = '0' + clkDate->Year / 10;
			dateStr[pos++] = '0' + clkDate->Year % 10;
			dateStr[pos++] = '.';
		}


		dateStr[pos-1] = '\0';
}

void Update_RTCTime(uint8_t h, uint8_t m, uint8_t s){
	if(h > 23) h = 0;
	if(m > 59) m = 0;
	if(s > 59) s = 0;

	clkTime.Hours = h;
	clkTime.Minutes = m;
	clkTime.Seconds = s;

	if (HAL_RTC_SetTime(&hrtc, &clkTime, RTC_FORMAT_BIN) != HAL_OK)
	{
	  Error_Handler();
	}
}
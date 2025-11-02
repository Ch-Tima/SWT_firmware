/*
 * RTCManager.c
 *
 *  Created on: Oct 20, 2025
 *      Author: tim
 */

#include "RTCManager.h"

extern RTC_HandleTypeDef hrtc;
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

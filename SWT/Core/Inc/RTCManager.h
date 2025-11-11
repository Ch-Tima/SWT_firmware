/*
 * RTCManager.h
 *
 *  Created on: Oct 20, 2025
 *      Author: Ch-Tima
 */

#ifndef INC_RTCMANAGER_H_
#define INC_RTCMANAGER_H_

#include "stm32f1xx_hal.h"

void Get_Time_Now(char *timeStr, RTC_TimeTypeDef *clkTime);

void Get_Date_Now(char *dateStr, uint8_t format, RTC_DateTypeDef *clkTime);

void Update_RTCTime(uint8_t h, uint8_t m, uint8_t s);

#endif /* INC_RTCMANAGER_H_ */

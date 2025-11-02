/*
 * UI_SetTime.c
 *
 *  Created on: Oct 20, 2025
 *      Author: tim
 */


#include "UI/UI_SetTime.h"

uint8_t hours = 0;
uint8_t minutes = 0;
uint8_t sec = 0;
char timeStr[8] = {0};
extern RTC_TimeTypeDef clkTime;

void UI_Time_Init(){
    hours = clkTime.Hours;
    minutes = clkTime.Minutes;
    sec = clkTime.Seconds;

    timeStr[0] = '0' + hours/10;
    timeStr[1] = '0' + hours % 10;
    timeStr[2] = ':';
    timeStr[3] = '0' + minutes/10;
    timeStr[4] = '0' + minutes % 10;
    timeStr[5] = ':';
    timeStr[6] = '0' + sec/10;
    timeStr[7] = '0' + sec % 10;
}

void UI_Time_Draw(){

    LCD_DrawText(4, 4, "SETUP_TIME:", 0);
    LCD_DrawText(8, 24, timeStr, 1);

}

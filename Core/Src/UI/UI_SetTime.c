/*
 * UI_SetTime.c
 *
 *  Created on: Nov 01, 2025
 *      Author: Ch-Tima
 */


#include "UI/UI_SetTime.h"

uint8_t hours = 0;
uint8_t minutes = 0;
uint8_t sec = 0;

uint8_t t = 0; // 0 - hours | 1 - minutes | 2 - sec

char timeStr[8] = {0};
extern RTC_TimeTypeDef clkTime;

void UI_Time_Init(){
    hours = clkTime.Hours;
    minutes = clkTime.Minutes;
    sec = clkTime.Seconds;
    update_timeStr();
}

void UI_Time_Draw(ButtonStatus_t btnup_status, ButtonStatus_t btndown_status){

    uint8_t *number;

    //SAVE
    if(btnup_status == BUTTON_HOLD){
        Update_RTCTime(hours, minutes, sec);
        //LCD_DrawText(64, 48, "$Save", 0);
        UI_SetView(MAIN_VIEW);
        return;
    }
    //NOT SAVE (BACK TO MAIN)
    if(btndown_status == BUTTON_HOLD){
        UI_SetView(MAIN_VIEW);
        return;
    }

    if(t == 0){
        number = &hours;
    }else if(t == 1){
        number = &minutes;
    }else{
        number = &sec;
    }

    //change the scale
    if(btnup_status == BUTTON_LONG){
        t = (t + 1) % 3;
    }

    if(btndown_status == BUTTON_LONG){
        t = (t == 0) ? 2 : t - 1;
    }
    //change the value
    if(btnup_status == BUTTON_SHORT){
        (*number)++;
        if(t == 0 && *number > 23){
            *number = 0;
        }
        else if(*number > 59){
            *number = 0;
        }
    }

    if(btndown_status == BUTTON_SHORT){
        if(*number == 0){
            *number = (t == 0) ? 23 : 59;
        }else (*number)--;
    }


    update_timeStr();

    LCD_DrawText(4, 4, "SETUP_TIME:", 0);
    LCD_DrawText(8, 24, timeStr, 1);
    LCD_DrawCharX2(15*(t*2+1)+(15*t), 40, '^');

}

void update_timeStr(){
    timeStr[0] = '0' + hours/10;
    timeStr[1] = '0' + hours % 10;
    timeStr[2] = ':';
    timeStr[3] = '0' + minutes/10;
    timeStr[4] = '0' + minutes % 10;
    timeStr[5] = ':';
    timeStr[6] = '0' + sec/10;
    timeStr[7] = '0' + sec % 10;
}

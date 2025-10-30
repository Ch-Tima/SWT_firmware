#include "UIManager.h"

static uint8_t currentScreen = MAIN_VIEW;

static char timeStr[9];
static char dateStr[13] = {0}; //WWW DD/MM/YY
static char batStr[8] = {0};
static char info[16] = {0};
static uint8_t dataFormat = 0b1111;//YYMMDDWW
static char tempC[16];

extern uint8_t rtc_tick;
extern RTC_TimeTypeDef clkTime;
extern RTC_DateTypeDef clkDate;

void UI_Init(){
    Get_Time_Now(timeStr, &clkTime);
    Get_Date_Now(dateStr, dataFormat, &clkDate);
}

void UI_Update(){

}

uint8_t UI_getCurrentScreen(){
    return currentScreen;
}

/*
 * UIManager.c
 *
 *  Created on: Oct 20, 2025
 *      Author: Ch-Tima
 */
#include "UIManager.h"

//LCD
static uint8_t currentScreen = MAIN_VIEW;
static uint8_t is_lcd_led_on = 1;

//DATE|TIME
static char timeStr[9];
static char dateStr[13] = {0}; //WWW DD/MM/YY
static uint8_t dataFormat = 0b1111;//YYMMDDWW

static char tempC[16];//temperature text buffer

//BATTERY
static float vbat = 0;//voltage
static uint16_t battery_level = 0;//percentage
static char batStr[8] = {0};//percentage as string

//MENU
MenuItem list_menu[] = {
    { "Set Time", UI_SET_TIME, 1 },
    { "Set Date", UI_SET_DATE, 0 },
    { "Setup Battery", UI_SETUP_BATTERY, 0 },
    { "Setup Click", UI_SETUP_CLK, 0 },
    { "About", UI_INFO, 0 }
};
static uint8_t currentMenuIndex = 0;
static uint8_t menuSize = sizeof(list_menu)/sizeof(MenuItem);

//OTHER
static char info[16] = {0};//Debug info

// External variables (provided by main.c or other modules)
extern uint8_t rtc_tick;
extern uint8_t adc1_tick;
extern uint16_t adc1_value_battery;
extern uint16_t adc1_value_thermistor;
extern RTC_TimeTypeDef clkTime;
extern RTC_DateTypeDef clkDate;

/*
 *  Initialize UI system
*/
void UI_Init(){
    Get_Time_Now(timeStr, &clkTime);
    Get_Date_Now(dateStr, dataFormat, &clkDate);
}

void UI_Update(){

//============BUTTONS_BEGIN============//
    ButtonStatus_t btnup_status = Buttons_GetState(BUTTON_UP);
    ButtonStatus_t btndown_status = Buttons_GetState(BUTTON_DOWN);

    if(currentScreen == MAIN_VIEW){
        //OFF/ON LIGHT
        //Handle LCD backlight control
    	if(btnup_status == BUTTON_LONG){
    		is_lcd_led_on = 1;//Long press turns backlight ON permanently
    	}else if (btnup_status == BUTTON_SHORT){
    		is_lcd_led_on = 0;//Short press turns backlight OFF
    	}
        //Update the backlight pin
    	if(btnup_status == BUTTON_HOLD || is_lcd_led_on){
    		HAL_GPIO_WritePin(LCD_LED_GPIO_Port, LCD_LED_Pin, GPIO_PIN_SET);
    	}else{
    		HAL_GPIO_WritePin(LCD_LED_GPIO_Port, LCD_LED_Pin, GPIO_PIN_RESET);
    	}
        //Open menu on DOWN short press
        if(btndown_status == BUTTON_SHORT){
            currentScreen = MENU_VIEW;
        }
    }else if(currentScreen == MENU_VIEW){
        if (btnup_status == BUTTON_HOLD){
            currentScreen = list_menu[currentMenuIndex].menuId;
            if(currentScreen == UI_SET_TIME){
                UI_Time_Init();
            }
        }else if(btndown_status == BUTTON_LONG){
            currentScreen = MAIN_VIEW;//GO BACK
        }
        

        if(btnup_status == BUTTON_SHORT){
            list_menu[currentMenuIndex].isSelect = 0;
            if(currentMenuIndex == 0){
                currentMenuIndex = menuSize-1;
            }else{
                currentMenuIndex--;
            }
            list_menu[currentMenuIndex].isSelect = 1;
        }else if(btndown_status == BUTTON_SHORT){
            list_menu[currentMenuIndex].isSelect = 0;
            if(currentMenuIndex >= menuSize-1){
                currentMenuIndex = 0;
            }else{
                currentMenuIndex++;
            }
            list_menu[currentMenuIndex].isSelect = 1;
        }
        
    }

//============BUTTONS_END============//

//============DRAW_BEGIN============//
    LCD_Clear();
    if(currentScreen == MAIN_VIEW){
        // Draw battery information
        if(HAL_GPIO_ReadPin(CHARG_GPIO_Port, CHARG_Pin) == GPIO_PIN_SET){
            LCD_DrawText(96, 4, batStr, 0);
        }else{
        	LCD_DrawText(88, 6, "~", 0);// Charging indicator
        	LCD_DrawText(96, 4, batStr, 0);
        }
        // Draw core UI elements
        LCD_DrawText(4, 16, timeStr, 1);//TIME
		LCD_DrawText(16, 36, dateStr, 0);//DATE
		LCD_DrawText(8, 48, tempC, 0);//TEMPERATURE


        LCD_DrawChar(100, 32, 'A');
    }else if (currentScreen == MENU_VIEW){
        // Draw simple static menu
        for(uint8_t i = 0; i < (sizeof(list_menu)/sizeof(MenuItem)); i++){
            if(list_menu[i].isSelect){
                LCD_DrawText(4, (4*(i*3)), ">", 0);
                LCD_DrawText(12, (4*(i*3)), list_menu[i].title, 0);
            }else{
                LCD_DrawText(4, (4*(i*3)), list_menu[i].title, 0);
            }
        }
        LCD_DrawChar(100, 32, 'B');
    }else if(currentScreen == UI_SET_TIME){
        UI_Time_Draw();
        LCD_DrawChar(100, 32, 't');
    }

    
    LCD_Update();   
//============DRAW_END============//

    
}

/*
 *  Update time/date data from RTC.
 *  Should be called when rtc_tick flag is set
*/
void UI_UpdateDataFromRTC(){
    Get_Time_Now(timeStr, &clkTime);
    if(clkTime.Hours == 0x00 && clkTime.Minutes == 0x00 && (clkTime.Seconds == 0x00)){
        Get_Date_Now(dateStr, dataFormat, &clkDate);
    }
}
/*
 *  Update temperature and battery data from ADC.
 *  Should be called when adc1_tick flag is set.
*/
void UI_UpdateDataFromADC(){
    Thermistor_strCalcTempC(tempC, adc1_value_thermistor);
    vbat = getVBat(adc1_value_battery);//TEST
    battery_level = getBatteryLevel(vbat);
    uint16ToCharArrEx(batStr, battery_level, '%');
}
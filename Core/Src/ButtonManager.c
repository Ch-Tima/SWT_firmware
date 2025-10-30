#include "ButtonManager.h"

static uint8_t press_tick_btnup = 0;
static uint8_t press_tick_btndown = 0;

ButtonStatus_t Buttons_GetState(ButtonID_t btn_id){
    GPIO_TypeDef *gpio;
    uint16_t pin;
    uint8_t *tick;

    if(btn_id == BUTTON_UP){
        gpio = BTN_UP_GPIO;
        pin = BTN_UP_PIN;
        tick = &press_tick_btnup;
    }else{
        gpio = BTN_DOWN_GPIO;
        pin = BTN_DOWN_PIN;
        tick = &press_tick_btndown;
    }

    uint8_t state = HAL_GPIO_ReadPin(gpio, pin);

    if(state == GPIO_PIN_RESET){
        if (*tick < 255) (*tick)++; 
        if (*tick > LONG_HOLD) {
            return BUTTON_HOLD; // удержание (держим)
        }
        return BUTTON_NONE;
    }else{
        if (*tick >= LONG_CLICK) {
            *tick = 0;
            return BUTTON_LONG;
        } 
        else if (*tick >= SHORT_CLICK) {
            *tick = 0;
            return BUTTON_SHORT;
        } 
        else {
            *tick = 0;
            return BUTTON_NONE;
        }
    }
}

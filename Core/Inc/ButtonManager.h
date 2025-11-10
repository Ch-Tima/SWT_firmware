

#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <stdint.h>
#include "main.h"
#include "stm32f103x6.h"

#define SHORT_CLICK 1
#define LONG_CLICK 35
#define HOLD_TICKS 75

typedef enum {
    BUTTON_NONE,
    BUTTON_SHORT,
    BUTTON_LONG,
    BUTTON_HOLD,
} ButtonStatus_t;

typedef enum{
    BUTTON_UP,
    BUTTON_DOWN
} ButtonID_t;

ButtonStatus_t Buttons_GetState(ButtonID_t btn_id);

#endif
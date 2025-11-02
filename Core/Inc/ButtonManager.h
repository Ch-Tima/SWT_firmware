#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include <stdint.h>
#include "main.h"
#include "stm32f103x6.h"

#define LONG_CLICK 50
#define LONG_HOLD 10
#define SHORT_CLICK 3

typedef enum {
    BUTTON_NONE,
    BUTTON_SHORT,
    BUTTON_LONG,
    BUTTON_HOLD
} ButtonStatus_t;

typedef enum{
    BUTTON_UP,
    BUTTON_DOWN
} ButtonID_t;

ButtonStatus_t Buttons_GetState(ButtonID_t btn_id);

#endif
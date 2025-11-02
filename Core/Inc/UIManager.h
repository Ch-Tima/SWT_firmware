#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <stdint.h>
#include "display.h"
#include "Battery.h"
#include "Thermistor.h"
#include "RTCManager.h"
#include "ButtonManager.h"
#include "Utils.h"
#include "main.h"

#define MAIN_VIEW 0xA
#define MENU_VIEW 0xB
#define UI_SET_TIME 0xB0
#define UI_SET_DATE 0xB1
#define UI_SETUP_BATTERY 0xB2
#define UI_SETUP_CLK 0xB3
#define UI_INFO 0xC

typedef struct {
    char *title;
    uint8_t menuId;
    uint8_t isSelect;
} MenuItem;

void UI_Init(void);
void UI_Update();
void UI_UpdateDataFromRTC();
void UI_UpdateDataFromADC();

#endif


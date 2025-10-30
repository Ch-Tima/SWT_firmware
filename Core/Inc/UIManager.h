#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <stdint.h>
#include "display.h"
#include "Battery.h"
#include "Thermistor.h"
#include "RTCManager.h"
#include "main.h"

#define MAIN_VIEW 0xA
#define MENU_VIEW 0xB
#define UI_SET_TIME 0xB0
#define UI_SET_DATE 0xB1
#define UI_SET_BATTERY 0xB2
#define UI_INFO 0xC

void UI_Init(void);
void UI_Update();
uint8_t UI_getCurrentScreen();

#endif


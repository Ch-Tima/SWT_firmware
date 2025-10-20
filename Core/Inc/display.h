/*
 * display.h
 *
 *  Created on: Oct 5, 2025
 *      Author: Ch-Tima
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "stm32f1xx_hal.h"

//#define LCD_A0_Pin GPIO_PIN_1
//#define LCD_A0_GPIO_Port GPIOB
//#define LCD_RST_Pin GPIO_PIN_10
//#define LCD_RST_GPIO_Port GPIOB
//#define LCD_CS_Pin GPIO_PIN_12
//#define LCD_CS_GPIO_Port GPIOB

//CD|A0
#define LCD_A0_Pin GPIO_PIN_4
#define LCD_A0_GPIO_Port GPIOA
//RST
#define LCD_RST_Pin GPIO_PIN_3
#define LCD_RST_GPIO_Port GPIOA
//CS
#define LCD_CS_Pin GPIO_PIN_2
#define LCD_CS_GPIO_Port GPIOA

void LCD_Init();
void LCD_Clear(void);
void LCD_Update(void);
void LCD_DrawPoint(uint8_t x, uint8_t y);
void LCD_DrawChar(uint8_t x, uint8_t y, char ch);
void LCD_DrawCharX2(uint8_t x, uint8_t y, char ch);
void LCD_DrawText(uint8_t x, uint8_t y, const char *text, uint8_t isScale);
#endif /* INC_DISPLAY_H_ */

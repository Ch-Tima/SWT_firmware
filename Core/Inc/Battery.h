/*
 * Battery.h
 *
 *  Created on: Oct 24, 2025
 *      Author: ch-tima
 */

#ifndef INC_BATTERY_H_
#define INC_BATTERY_H_

#include <stdint.h>

#define MAX_V 4.19f
#define MIN_V 3.0f
#define NORMAL_VCC 3.3f
#define DIVIDER_RATIO 2.0f
#define ADC_MAX 4095.0f

float getVBat(uint16_t adc_value);

float getBatteryLevel(float vbat);

#endif /* INC_BATTERY_H_ */

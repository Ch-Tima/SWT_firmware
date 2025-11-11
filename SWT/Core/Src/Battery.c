/*
 * Battery.c
 *
 *  Created on: Oct 24, 2025
 *      Author: tim
 */

#include "Battery.h"


float getVBat(uint16_t adc_value){
	return ((float)adc_value / ADC_MAX) * NORMAL_VCC * DIVIDER_RATIO;
}

float getBatteryLevel(float vbat){
	if(vbat <= 0.0f) return 0.0f;
	return ((vbat - MIN_V) / (MAX_V - MIN_V)) * 100.0f;
}

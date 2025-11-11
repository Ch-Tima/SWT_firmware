/*
 * Battery.c
 *
 *  Created on: Oct 24, 2025
 *      Author: Ch-Tima
 * 
 * SWT
 * Copyright (C) 2025  <Ch-Tima>
 *
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "Battery.h"

float getVBat(uint16_t adc_value){
	return ((float)adc_value / ADC_MAX) * NORMAL_VCC * DIVIDER_RATIO;
}

float getBatteryLevel(float vbat){
	if(vbat <= 0.0f) return 0.0f;
	return ((vbat - MIN_V) / (MAX_V - MIN_V)) * 100.0f;
}

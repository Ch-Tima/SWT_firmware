/*
 * Battery.h
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

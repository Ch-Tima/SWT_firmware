/*
 * Thermistor.h
 *
 *  Created on: Oct 20, 2025
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

#ifndef INC_THERMISTOR_H_
#define INC_THERMISTOR_H_

#define A 0.0008397788656f
#define B 0.0002006238973f
#define C 0.0000001356660f
#define R_FIXED 10980.0f
#define ADC_MAX 4095.0f

#include <math.h>
#include <stdint.h>

float Thermistor_CalcTempC(uint16_t adcValue);

void Thermistor_strCalcTempC(char *buf, uint16_t adcValu);

#endif /* INC_THERMISTOR_H_ */

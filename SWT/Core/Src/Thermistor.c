/*
 * Thermistor.c
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
#include "Thermistor.h"

float Thermistor_CalcTempC(uint16_t adcValue){
	  if (adcValue > 0 && adcValue < ADC_MAX)
	  {
		  float adc = (float)adcValue;
		  float Ntc_log = logf(R_FIXED * (adc / (ADC_MAX - adc)));
		  return (1.0f / (A + B*Ntc_log + C*Ntc_log*Ntc_log*Ntc_log)) - 273.15f;
	  }
	  else
	  {
	      return 0;
	  }

}

void Thermistor_strCalcTempC(char *buf, uint16_t adcValu){
	float temp = Thermistor_CalcTempC(adcValu);
	char *p = buf;

	if (temp > 0) *p++ = '+';
    else if (temp < 0) {
    	*p++ = '-';
    	temp = -temp;
    }

	uint16_t whole = (uint16_t)temp;
	uint16_t frac = (uint16_t)((temp-(float)whole)*10.1f);

	uint16_t div = 1;
	while (whole/div >= 10) {
        div *= 10;
	}

    while (div > 0){
    	*p++ = whole / div + '0';
    	whole %= div;
    	div /= 10;
    }

    *p++ = '.';
    *p++ = frac + '0';
    *p++ = '\0';

}

/*
 * Utils.c
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

#include "Utils.h"

void floatToCharArr(char *buf, float value){
    uint16ToCharArrEx(buf, value, '\0');
}

void uint16ToCharArrEx(char *buf, uint16_t value, char lastChar){
	char *p = buf;

	uint16_t whole = (uint16_t)value;

	uint16_t div = 1;
	while (whole/div >= 10) {
        div *= 10;
	}

    while (div > 0){
    	*p++ = whole / div + '0';
    	whole %= div;
    	div /= 10;
    }

    if (lastChar != '\0')
        *p++ = lastChar;

    *p++ = '\0';

}


void uint16ToCharArr(char *buf, uint16_t value){
    uint16ToCharArrEx(buf, value, '\0');
}

void floatToCharArrEx(char *buf, float value, char lastChar){
	char *p = buf;

	if (value < 0) {
		value = -value;
    }

	uint16_t whole = (uint16_t)value;
	uint16_t frac = (uint16_t)((value-(float)whole)*10.1f);

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

    if (lastChar != '\0')
        *p++ = lastChar;

    *p++ = '\0';

}

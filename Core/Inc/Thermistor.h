/*
 * Thermistor.h
 *
 *  Created on: Oct 20, 2025
 *      Author: tim
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

#endif /* INC_THERMISTOR_H_ */

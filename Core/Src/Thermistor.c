/*
 * Thermistor.c
 *
 *  Created on: Oct 20, 2025
 *      Author: tim
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

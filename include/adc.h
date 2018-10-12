#ifndef ADC_H
#define ADC_H

#include "common.h"
/*
 * Returns: ADC value of Channel specified
 * Does one conversion at a time on a single channel
 * Scan conversion not needed due to low polling rate
 */
uint32_t single_ended_adc(uint32_t Channel);

#endif

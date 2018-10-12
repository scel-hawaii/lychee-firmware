#include "battery.h"
#include "adc.h"

#define PA2 ADC_CHANNEL_2

uint32_t read_battery_voltage(void) {
	uint32_t value = -1;
	value = single_ended_adc(PA2) * VDD / ADC_RESOLUTION;
	return value;
}

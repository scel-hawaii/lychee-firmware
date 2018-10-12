#include "sp212.h"
#include "adc.h"

#define PA0 ADC_CHANNEL_1

uint32_t sp212_read(void) {
	uint32_t voltage;
	uint32_t raw_val;
	
	// 0.5 W m^-2 per mv
	float conversion_factor = 0.5;
	 
	raw_val = single_ended_adc(PA0);

	printf("Raw ADC Value: %ld\r\n", raw_val);
	// convert 12 bit adc value w/ 3300 mv
	voltage = raw_val * 3300 / 4095;

	printf("Voltage Value: %ld\r\n", voltage);
	// Return W m^2 value
	return (float) voltage * conversion_factor;


}

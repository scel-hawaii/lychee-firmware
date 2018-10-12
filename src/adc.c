#include "adc.h"

uint32_t single_ended_adc(uint32_t Channel) {
	uint32_t value = -1;
	ADC_ChannelConfTypeDef sConfig;

	sConfig.Channel = Channel;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.SamplingTime = ADC_SAMPLETIME_19CYCLES_5;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;

	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
	  _Error_Handler(__FILE__, __LINE__);
	}

	HAL_ADC_Start(&hadc1);

	if(HAL_ADC_PollForConversion(&hadc1, 1000000) == HAL_OK) {
			value = HAL_ADC_GetValue(&hadc1);
	}

	HAL_ADC_Stop(&hadc1);

	return value;
}

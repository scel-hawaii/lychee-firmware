#ifndef COMMON_H
#define COMMON_H

#include "stm32f3xx_hal.h"
#include "cmsis_os.h"

#define TRUE 1
#define FALSE 0

#define VDD 3300
#define ADC_RESOLUTION 4095

extern ADC_HandleTypeDef hadc1;

extern I2C_HandleTypeDef hi2c1;

extern SPI_HandleTypeDef hspi1;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

extern osThreadId defaultTaskHandle;
extern osThreadId serialTaskHandle;
extern osThreadId bmeTaskHandle;
osThreadId adcTaskHandle;

#endif

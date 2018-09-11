#ifndef COMMON_H
#define COMMON_H

#include "stm32f3xx_hal.h"
#include "cmsis_os.h"
#include "serial_logging.h"

extern ADC_HandleTypeDef hadc1;

extern I2C_HandleTypeDef hi2c1;

extern SPI_HandleTypeDef hspi1;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

extern osThreadId defaultTaskHandle;
extern osThreadId serialTaskHandle;
extern osThreadId bmeTaskHandle;

#endif

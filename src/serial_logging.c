#include "serial_logging.h"

#define TX_BUFFER 100

void serial_println(UART_HandleTypeDef *huart, char *data) {
	char string[TX_BUFFER];
	memset(string, 0, sizeof(string));
	sprintf(string, "%s\n\r", data);
	HAL_UART_Transmit(huart, (uint8_t *) string, sizeof(string), 1000);
}

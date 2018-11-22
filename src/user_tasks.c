#include "user_tasks.h"
#include "bme280_user.h"
#include "sp212.h"
#include "adc.h"
#include "battery.h"
#include "xbee.h"

void SerialTask(void) {
	// Setup Buffer for printf
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

	for(;;) {
		int integer = 3;
		printf("This number is %d\n\r", integer);
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_10);
		HAL_Delay(2000);
	}
}

void StartBMETask(void) {
	struct bme280_dev dev;
	int8_t rslt = BME280_OK;

	if (bme280_init_user(&dev) != rslt) {
		printf("Device not initialized\r\n");
	}

	printf("Chip ID: %d\r\n", dev.chip_id);

	bme280_read_forced_mode(&dev);

}

void StartADCTask(void) {
	uint32_t adc_value;
	TickType_t xLastWakeTime = xTaskGetTickCount();

	for(;;) {
		adc_value = sp212_read();
		printf("Pyranometer Value: %ld\n\r", adc_value);
		printf("Battery: %ld\n\r", read_battery_voltage());
		vTaskDelayUntil( &xLastWakeTime,  3000);
	}

}


void StartXbeeTask(void) {
	xbee_request_t xbee;
	uint8_t payload[2];
	payload[0] = 'H';
	payload[1] = 'L';

	uint8_t len = sizeof(payload);
	xbee_createRequest(&xbee, 0x0, 0x0, (uint8_t *) &payload, len);

	for(;;) {
		xbee_send(&xbee);
		HAL_Delay(3000);
	}
}

#include "user_tasks.h"


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
		printf("Device not intialized\r\n");
	}

	printf("Chip ID: %d\r\n", dev.chip_id);

	bme280_read_forced_mode(&dev);

}

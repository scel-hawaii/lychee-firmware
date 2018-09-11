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
	for(;;) {
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_9);
		HAL_Delay(2000);
	}

}

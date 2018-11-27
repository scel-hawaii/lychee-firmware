#include "bme280_user.h"

//#define I2C 1
#define SPI 1
int8_t bme280_init_user(struct bme280_dev *dev) {
	int8_t rslt = BME280_OK;
	uint8_t settings_sel;

	/* Sensor_0 interface over SPI with native chip select line */
#ifdef SPI
	/* Sensor_0 interface over SPI with native chip select line */
	dev->dev_id = 0;
	dev->intf = BME280_SPI_INTF;
	dev->read = bme280_spi_read;
	dev->write = bme280_spi_write;
	dev->delay_ms = bme280_delay;
#elif I2C // DOES NOT WORK CURRENTLY
	dev->dev_id = BME280_I2C_ADDR_PRIM;
	dev->intf = BME280_I2C_INTF;
	dev->read = bme280_i2c_read;
	dev->write = bme280_i2c_write;
	dev->delay_ms = bme280_delay;
#endif

	rslt = bme280_init(dev);

	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_1X;
	dev->settings.osr_t = BME280_OVERSAMPLING_1X;

	settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, dev);

	return rslt;
}

int8_t bme280_read_forced_mode(struct bme280_dev *dev) {
	int8_t rslt;
	uint8_t settings_sel;
	struct bme280_data comp_data;
	uint8_t mode;

	/* Recommended mode of operation: Weather Monitoring */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_1X;
	dev->settings.osr_t = BME280_OVERSAMPLING_1X;

	settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL;

rslt = bme280_set_sensor_settings(settings_sel, dev);
	printf("Temperature, Pressure, Humidity\r\n");
	/* Continuously stream sensor data */
	while (1) {
rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
		rslt = bme280_get_sensor_mode(&mode, dev);
		printf("Sensor Mode: 0x%x\r\n", mode);

	    /* Wait for the measurement to complete and print data @25Hz */
	    dev->delay_ms(40);
	    rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
	    print_sensor_data(&comp_data);
	    dev->delay_ms(3000);
	}
	return rslt;
}

void print_sensor_data(struct bme280_data *comp_data) {
#ifdef BME280_FLOAT_ENABLE
        printf("%0.2f, %0.2f, %0.2f\r\n",comp_data->temperature, comp_data->pressure, comp_data->humidity);
#else
        printf("%ld, %ld, %ld\r\n",comp_data->temperature, comp_data->pressure, comp_data->humidity);
#endif
}

/*
 * After a success read on the first register, the BME280 auto-increments to the next register
 * So you can perform another read to get the next register's data.
 * To handle this we loop and get data one register at a time until the length given
 */
int8_t bme280_spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {

	int8_t rslt = 0;

	// Toggle control pin
	HAL_GPIO_WritePin(BME_CS_BANK, BME_CS_PIN, 0);

	// Send control byte
	if (HAL_SPI_Transmit(&hspi1, &reg_addr, 1, 1000) != HAL_OK) {
		rslt = 1;
	}

	// Read data from address(es)
	for(int read_count = 0; read_count < len; read_count++) {
		uint8_t temp_data;
		if (HAL_SPI_Receive(&hspi1, &temp_data, 1, 1000) != HAL_OK) {
			rslt = 1;
		}
		// Put data into return array
		reg_data[read_count] = temp_data;
	}
	HAL_GPIO_WritePin(BME_CS_BANK, BME_CS_PIN, 1);

	return rslt;

}


/*
 * For multi-byte writes all subsequent register addresses are stored in reg_data
 * this was designed by the creator of the BME API
 * Luckily HAL library handles this well. So we don't need a loop.
 * Ex. 1st write: reg_addr -> reg_data -> reg_data(contains next address) -> reg_data and so on.
 * */
int8_t bme280_spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
	int8_t rslt = 0;
	HAL_GPIO_WritePin(BME_CS_BANK, BME_CS_PIN, 0);

	if (HAL_SPI_Transmit(&hspi1, &reg_addr, 1, 1000) != HAL_OK) {
		rslt = 1;
	}
	if (HAL_SPI_Transmit(&hspi1, reg_data, 1, 1000) != HAL_OK) {
				rslt = 1;
	}

	HAL_GPIO_WritePin(BME_CS_BANK, BME_CS_PIN, 1);
	return rslt;
}

// I2C Function don't quite work. We have enough pins for SPI

int8_t bme280_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
	int8_t rslt = 0;
	if (HAL_I2C_Mem_Read(&hi2c1, (uint16_t) dev_id,
			(uint16_t) reg_addr, I2C_MEMADD_SIZE_8BIT, reg_data, len, 1000) != HAL_OK) {
		rslt = 1;
	}
	return rslt;
}
int8_t bme280_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
	int8_t rslt = 0;
	if (HAL_I2C_Mem_Write(&hi2c1, (uint16_t) dev_id,
				(uint16_t) reg_addr, I2C_MEMADD_SIZE_8BIT, reg_data, len , 1000) != HAL_OK) {
			rslt = 1;
		}
	return rslt;
}

void bme280_delay(uint32_t period) {
	//Taken from FreeRTOS vTaskDelayUntil example
	TickType_t xLastWakeTime;
	const TickType_t xFrequency = period;

	// Initialize the xLastWakeTime variable with the current time.
	xLastWakeTime = xTaskGetTickCount();

	vTaskDelayUntil(&xLastWakeTime, xFrequency);
}


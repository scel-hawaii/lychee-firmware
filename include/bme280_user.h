#ifndef BME280_USER_H
#define BME280_USER_H

#include "common.h"
#include "bme280.h"

#define BME_CS_PIN GPIO_PIN_8
#define BME_CS_BANK GPIOE

int8_t bme280_init_user(struct bme280_dev *dev);

int8_t bme280_spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t bme280_spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

int8_t bme280_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t bme280_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

void bme280_delay(uint32_t period);

int8_t bme280_read_forced_mode(struct bme280_dev *dev);

void print_sensor_data(struct bme280_data *comp_data);

#endif

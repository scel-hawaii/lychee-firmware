#include "board.h"


void board_init(board_t *b) {
	printf("Board Init Phase\n\r");
	b->payload.schema = 7;
	b->payload.node_address = 0xEF;
	board_setup_sensor(b);
}

void board_setup_sensor(board_t *b){
	printf("Sensor Init Phase\n");
	if (bme280_init_user(&(b->bme280)) != BME280_OK) {
		printf("BME280 not initialized\r\n");
	}
}

void board_sample(board_t *b) {
	printf("Sampling Sensor\n\r");
	struct bme280_data comp_data;
	bme280_set_sensor_mode(BME280_FORCED_MODE, &(b->bme280));
	bme280_get_sensor_data(BME280_ALL, &comp_data, &(b->bme280));

	//print_sensor_data(&comp_data);


	payload_t *payload = &(b->payload);
	payload->battery_millivolts = read_battery_voltage();
	payload->panel_millivolts = 0;
	payload->sp212_irradiance_watts_per_square_meter = sp212_read();
	payload->bme280_humidity_centipercent = comp_data.humidity / 10;
	payload->bme280_pressure_pascal = comp_data.pressure;
	payload->bme280_temperature_centicelsius = comp_data.temperature;
	payload->uptime_milliseconds = HAL_GetTick();
}

void board_transmit_data(board_t *b) {
	printf("Transmitting Payload\n\r");
	xbee_createRequest(&(b->request), 0x0, 0x0, (uint8_t *) &(b->payload), sizeof(b->payload));
	xbee_send(&(b->request));
}

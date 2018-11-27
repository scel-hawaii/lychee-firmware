#ifndef BOARD_H
#define BOARD_H

#include "bme280_user.h"
#include "sp212.h"
#include "battery.h"
#include "xbee.h"
#include "common.h"

typedef struct {
    uint16_t schema;
    uint16_t node_address;
    uint32_t uptime_milliseconds;                        // Time since start of program
    uint16_t battery_millivolts;                         // Battery Voltage (in milli volts)
    uint16_t panel_millivolts;                           // Panel Voltage (in milli volts)
    uint32_t bme280_pressure_pascal;                    // Pressure Value (in pascals)
    uint16_t bme280_temperature_centicelsius;                 // Temperature Value (in celsius) (ideally we change this to Kelvin)
    uint16_t bme280_humidity_centipercent;                    // Humidity Value (in percentage)
    uint16_t sp212_irradiance_watts_per_square_meter;   // Solar Irradiance Value (in w/m^2)
} payload_t;

typedef struct {
	payload_t payload;
	xbee_request_t request;
	struct bme280_dev bme280;


	uint32_t lastms;
	uint16_t node_address;

} board_t;

void board_init(board_t *b);
void board_sample(board_t *b);
void board_transmit_data();

void board_setup_sensor(board_t *b);


#endif

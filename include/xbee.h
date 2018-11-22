#ifndef XBEE_H
#define XBEE_H

#include "common.h"

#define START_BYTE 0x7e
#define ESCAPE 0x7d
#define XON 0x11
#define XOFF 0x13

#define ZB_TX_API_LENGTH 12

#define ZB_TX_REQUEST 0x10
#define DEFAULT_FRAME_ID 1
#define ZB_BROADCAST_RADIUS_MAX_HOPS 0
#define ZB_TX_UNICAST 0
#define ZB_BROADCAST_ADDRESS 0xfffe


typedef struct {
	uint32_t addr64_sh;
	uint32_t addr64_sl;
	uint16_t addr16;

	uint8_t broadcastRadius;
	uint8_t option;

	uint8_t *payload;
	uint8_t payload_length;

	uint8_t apiId;
	uint8_t frameId;
} xbee_request_t;

void xbee_writeByte(uint8_t b, uint8_t escape);
void xbee_send(xbee_request_t *req);
uint8_t xbee_getFrameDataLength(uint8_t payload_length);
uint8_t xbee_getFrameData(xbee_request_t *request, uint8_t pos);
void xbee_createRequest(xbee_request_t *request, uint32_t addr64_sh, uint32_t addr64_sl,
						uint8_t *payload, uint8_t payload_length);

#endif

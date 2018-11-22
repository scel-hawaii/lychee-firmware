#include "xbee.h"

void xbee_send(xbee_request_t *req) {
	xbee_writeByte(START_BYTE, FALSE);

	uint8_t payload_len = xbee_getFrameDataLength(req->payload_length);

	// send length
	uint8_t msbLen = ((payload_len + 2) >> 8) & 0xff;
	uint8_t lsbLen = (payload_len + 2) & 0xff;

	xbee_writeByte(msbLen, TRUE);
	xbee_writeByte(lsbLen, TRUE);

	// api id
	xbee_writeByte(req->apiId, TRUE);
	xbee_writeByte(req->frameId, TRUE);

	uint8_t checksum = 0;

	// compute checksum, start at api id
	checksum+= req->apiId;
	checksum+= req->frameId;

	for (int i = 0; i < payload_len; i++) {
		xbee_writeByte(xbee_getFrameData(req, i), TRUE);
		checksum+= xbee_getFrameData(req, i);
	}

	// perform 2s complement
	checksum = 0xff - checksum;

	// send checksum
	xbee_writeByte(checksum, TRUE);
}

void xbee_writeByte(uint8_t b, uint8_t escape) {
	uint8_t esc = ESCAPE;
	if (escape && (b == START_BYTE || b == ESCAPE || b == XON || b == XOFF)) {
		HAL_UART_Transmit(&huart2, (uint8_t *) &esc, 1, 1000);
		HAL_UART_Transmit(&huart2, (uint8_t *) &b, 1, 1000);
	}
	else {
		HAL_UART_Transmit(&huart2, (uint8_t *) &b, 1, 1000);
	}
}

void xbee_createRequest(xbee_request_t *request, uint32_t addr64_sh, uint32_t addr64_sl,
		uint8_t *payload, uint8_t payload_length) {

	request->addr16 = ZB_BROADCAST_ADDRESS;
	request->broadcastRadius = ZB_BROADCAST_RADIUS_MAX_HOPS;
	request->option = ZB_TX_UNICAST;
	request->apiId = ZB_TX_REQUEST;
	request->frameId = DEFAULT_FRAME_ID;

	request->addr64_sh = addr64_sh;
	request->addr64_sl = addr64_sl;
	request->payload = payload;
	request->payload_length = payload_length;

}

uint8_t xbee_getFrameDataLength(uint8_t payload_length) {
	return ZB_TX_API_LENGTH + payload_length;
}

uint8_t xbee_getFrameData(xbee_request_t *req, uint8_t pos) {
	switch(pos) {
	case 0:
		return (req->addr64_sh >> 24) & 0xff;
		break;
	case 1:
		return (req->addr64_sh  >> 16) & 0xff;
		break;
	case 2:
		return (req->addr64_sh >> 8) & 0xff;
		break;
	case 3:
		return (req->addr64_sh) & 0xff;
		break;
	case 4:
		return (req->addr64_sl >> 24) & 0xff;
		break;
	case 5:
		return  (req->addr64_sl >> 16) & 0xff;
		break;
	case 6:
		return (req->addr64_sl >> 8) & 0xff;
	case 7:
		return req->addr64_sl & 0xff;
		break;
	case 8:
		return (req->addr16 >> 8) & 0xff;
	case 9:
		return req->addr16 & 0xff;
	case 10:
		return req->broadcastRadius;
	case 11:
		return req->option;
	default:
		return req->payload[pos - ZB_TX_API_LENGTH];
	}
	return 0;
}

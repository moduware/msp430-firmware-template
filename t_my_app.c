/*
 * t_my_app.c
 * msp430 firmware template
 * Receive messages from tile
 */

#include <np_module_mdk_v1.h>
#include "t_my_app.h"
#include "NCN_GPIO.h"

/**
 * Receive message from tile - use range from 0x2700 to 0x27ff
 * - Data: unsigned chart - 1byte element, 57 byte max length
 * acknowledge (ack) message - use range from 0x2700 to 0x27ff
 * - ack Data: unsigned chart - success: 0x00, fail: 0x01
**Suggested**
* use odd for receive message - example: 0x2700
* use even for ack message - example: 0x2701
* rename function(s) according to message definition on tmain
*/

void my_function_CMD_2700 (unsigned char*pData, unsigned char len) {

	// Feedback to Command 0x2700
		unsigned char response = 0x00;
		np_api_upload(0x2701, &response, 1);

}

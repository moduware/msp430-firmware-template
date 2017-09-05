/*
 * t_my_app.c
 * TEMPLATE
 */

#include <np_module_mdk_v1.h>
#include "t_my_app.h"
#include "NCN_GPIO.h"

//Perform module's function
//Receive command - use range from 0x2700 to 0x27ff
// **Suggested**
// odd number for command number
// even number for response command number


void my_function_CMD_2700 (unsigned char*pData, unsigned char len) {

	// Feedback to Command 0x2700
		unsigned char response = 0x00;
		np_api_upload(0x2701, &response, 1);

}

/*
 * t_my_app.c
 * LCD
 */

#include <np_module_mdk_v1.h>
#include "t_my_app.h"
#include "NCN_GPIO.h"
#include "LiquidCrystal.h"

//Perform module's function
//Receive command - use range from 0x2700 to 0x27ff
// **Suggested**
// odd number for command number
// even number for response command number

unsigned char apptext_1[16] = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
							0x20,0x20,0x20,0x20,0x20,0x20};
unsigned char apptext_2[16] = {0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
							0x20,0x20,0x20,0x20,0x20,0x20};

void text_1(unsigned char*pData, unsigned char len) {

	int i =0;
	for(i = 0  ; i < len; i++){
		apptext_1[i] = pData[i];						//Write pData from app and write to apptext array
	}
	if(len < 16){
		for(i = len  ; i < 16; i++){
			apptext_1[i] = 0x20;						//Write space character to columns without data from app
		}
	}

	LCD_SetCursor(0, 0);								//Set cursor on column and line 0
	LCD_Write_Byte(apptext_1,16);						//Write apptext_1 array to LCD

	// Feedback to Command 0x2701
		unsigned char response = 0x00;
		np_api_upload(0x2701, &response, 1);

}
void text_2(unsigned char*pData, unsigned char len) {

	int i =0;
	for(i = 0  ; i < len; i++){
		apptext_2[i] = pData[i];
	}
	if(len < 16){
		for(i = len  ; i < 16; i++){
			apptext_2[i] = 0x20;
		}
	}

	LCD_SetCursor(0, 1);
	LCD_Write_Byte(apptext_2,16);

	// Feedback to Command 0x2701
		unsigned char response = 0x00;
		np_api_upload(0x2701, &response, 1);

}

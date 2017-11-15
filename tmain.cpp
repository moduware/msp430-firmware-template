/**
 * msp430 mdk v1 firmware template
 **
 * Library declaration
 * np_module_mdk_v1 library for module gateway communication
 * NCN_GPIO library for MSP module pin configuration
 * remove unused libraries under library folder
 * add new libraries to use under library folder and link under project properties, declaration bellow
 */
#include <np_module_mdk_v1.h>
#include "t_my_app.h"
#include "NCN_GPIO.h"
#include "LiquidCrystal.h"
#include "I2C.h"

#define length 2
/*
 * Declaration for message function
 */
void LineText1(unsigned char*pData, unsigned char len);
void LineText2(unsigned char*pData, unsigned char len);

/*
 * Receive message(s) table declaration - use range from 0x2700 to 0x27ff
 * - Specify number of messages (length of the table): MDK_REGISTER_CMD message_table[length]
 * - Define message - example: {0x2700, SensorValue}
 */
const MDK_REGISTER_CMD message_table[length] = {
        {0x2700, LineText1},
        {0x2700, LineText2}
};

/**
 * PIN mode and variables initialization, start using libraries
 * set firmware version: np_api_set_app_version(x, x, x); - optional
 * set np_api_pm_automode_set() for running no_api_loop() once
 */
void np_api_setup() {
    // receive message range check. Keep structure for receive message event
    if ( np_api_register((MDK_REGISTER_CMD*)message_table, length) == MDK_REGISTER_FAIL ) {
    delay(1);
    }



}

/**
 * np_api_loop() runs continuously when the MCU is not on sleep mode - np_api_pm_automode_set() is not set
 * To exit auto power save mode use np_api_pm_automode_clear()
 * handle send message function: np_api_upload(messageType, data, length)
 * Send message to tile - use 0x2800
 * data: unsigned char - 1byte element, 57 byte max length
 * length: corresponding to amount of data byte
 * example: np_api_upload(0x2800, SensorValue, 2)
 */
void np_api_loop() {



}

/*
 * Start module's function
 * Initialize module application (or sensor, sensor drivers) if needed
 * Example: Air Contaminants module requires heating before using the sensor
 * Ethanol_heat_on() - function to start heating the module used under np_api_start()function
 */

void np_api_start() {

}

/*
 * Stop module's function
 * Stop module application (or sensor, sensor drivers) if needed
 * Example: Air Contaminants module has to stop heating function after the module is in LPM or off
 * Ethanol_heat_off() - function to stop the module used under np_api_stop()function
 */
void np_api_stop() {



}

/**
 * Receive message from tile - use range from 0x2700 to 0x27ff
 * - Data: unsigned chart - 1byte element, 57 byte max length
 * acknowledge (ack) message - use range from 0x2700 to 0x27ff
 * - ack Data: unsigned chart - success: 0x00, fail: 0x01
** Suggested **
* use odd for receive message - example: 0x2700
* use even for ack message - example: 0x2701
*/

void LineText1 (unsigned char*pData, unsigned char len) {
    int i =0;
    for(i = 0  ; i < len; i++) {
        apptext_1[i] = pData[i];                        //Write pData from app and write to apptext array
        }
    if(len < 16) {
        for(i = len  ; i < 16; i++) {
            apptext_1[i] = 0x20;                        //Write space character to columns without data from app
            }
    }
    LCD_SetCursor(0, 0);                                //Set cursor on column and line 0
    LCD_Write_Byte(apptext_1,16);                       //Write apptext_1 array to LCD

    // Feedback to Command 0x2701
    unsigned char response = 0x00;
    np_api_upload(0x2701, &response, 1);
}

void LineText2 (unsigned char*pdata, unsigned char len) {
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


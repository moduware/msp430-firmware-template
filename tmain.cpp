/**
 * t_my_app.c
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


/*
 * Receive message(s) table declaration - use range from 0x2700 to 0x27ff
 * - Specify number of messages (length of the table): MDK_REGISTER_CMD message_table[length]
 * - Define message - example: {0x2700, SensorValue}
 */
const MDK_REGISTER_CMD message_table[1] = {
        {0x2700, HandleMessageType},
};

/**
 * PIN mode and variables initialization, start using libraries
 * set firmware version: np_api_set_app_version(x, x, x); - optional
 * set np_api_pm_automode_set() for running no_api_loop() once
 */
void np_api_setup() {
    // receive message range check. Keep structure for receive message event
    if ( np_api_register((MDK_REGISTER_CMD*)message_table, 1) == MDK_REGISTER_FAIL ) {
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

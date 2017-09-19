/*
 * np_module_mdk_v1.h
 *
 *  Created on: 2015-12-8
 *      Author: coody
 */

#ifndef NP_MODULE_MDK_V1_H_
#define NP_MODULE_MDK_V1_H_

typedef void (*my_VOID_UCUC)(unsigned char*, unsigned char);

typedef struct {
	unsigned short 	command;
	my_VOID_UCUC	function;
} MDK_REGISTER_CMD;

#define MDK_REGISTER_SUCCESS	0x00
#define MDK_REGISTER_FAIL		0x01

#ifdef __cplusplus
	extern "C" {
#endif


inline void delay(unsigned int x) {while (x--) __delay_cycles(16000);}



void np_api_setup();
void np_api_loop();
void np_api_start();
void np_api_stop();
void np_api_download();
void np_api_poweroff();
/*
 * Description: API to set app firmware version
 * Parameter: null
 * Return: null
 *
 * Author: Coody.Liu
 *
 * Copyright: NexPack.Ltd
 */
void np_api_set_app_version(unsigned char HV, unsigned  char MV, unsigned char LV);
/*
 * Description: API to register developer's own Command for their module
 * Parameter: null
 * Return: null
 *
 * Author: Coody.Liu
 *
 * Copyright: NexPack.Ltd
 */
unsigned char np_api_register(MDK_REGISTER_CMD* cmd_func_table, unsigned char num);
/*
 * Description: API to upload data to Gateway/Phone
 * Parameter: null
 * Return: null
 *
 * Author: Coody.Liu
 *
 * Copyright: NexPack.Ltd
 */
unsigned char np_api_upload(unsigned int rcmd,unsigned char *pData, unsigned char pLen);
/*
 * Description: set auto power save mode
 * Parameter: null
 * Return: null
 *
 * Author: Coody.Liu
 *
 * Copyright: NexPack.Ltd
 */
void np_api_pm_automode_set(void);
/*
 * Description: exit auto power save mode
 * Parameter: null
 * Return: null
 *
 * Author: Coody.Liu
 *
 * Copyright: NexPack.Ltd
 */
void np_api_pm_automode_clear(void);
/*
 * Description: API to set a manually output address for next POST message
 * Parameter: null
 * Return: null
 *
 * Author: Coody.Liu
 *
 * Copyright: NexPack.Ltd
 */
void np_api_set_post_address(unsigned char address);
/*
 * Description: API to run the loop once at the auto power save mode
 * Parameter: null
 * Return: null
 *
 * Author: Coody.Liu
 *
 * Copyright: NexPack.Ltd
 */
unsigned char np_api_run_loop_once(void);
unsigned char np_api_upload_to_station(unsigned int rcmd, unsigned char *pData, unsigned char pLen);
#ifdef __cplusplus
	}
#endif

#endif /* NP_MODULE_MDK_V1_H_ */

/*
 * HC_SR04.h
 *
 *  Created on: 24/06/2016
 *      Author: MSJ
 */

#ifndef HC_SR04_H_
#define HC_SR04_H_

//Total clock time equivalent to the wide of the echo response
extern short unsigned ClockTime;
//Trigger to indicate the finish of interrupt service routine.
extern unsigned int finish_measurament;

class HC_SR04_class {

private:
	// Internal library's function to capture the echo wide
	inline void Echo(void);

public:
	// Clock and MCU settings
	void Initialitzation(void);
	// Function to initialize the Trigger and the measurement
	void Trigger(void);
};
extern HC_SR04_class US_s;

#endif /* HC_SR04_H_ */

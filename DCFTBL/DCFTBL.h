/*
 * Dummy.h
 *
 *  Created on: 06.04.2019
 *      Author: Tobias
 */
#include <Arduino.h>
#ifndef DCFTBL_H_
#define DCFTBL_H_

namespace TBL {

#define PULSEWIDTHTOLERANCE 20		// +/- 20ms tolerance to deteced 100ms / 200ms pulse
#define SECONDWIDTHTOLERANCE 100
#define MINUTEWIDTHTOLERANCE 20

typedef struct  {
		unsigned short value;
		bool valid;
		} dcfBit ;

typedef struct {
	 int second;
	 int minute;
	 int hour;
	 int dayOfWeek;
	 int day;
	 int month;
	 int year;
	 short signalQuality;
	} dcfTime;

class DCFTBL {

public:
	DCFTBL(	int DCF77Pin,						//Arduino pin where DCF Receiver is attached
			int DCFMonitorPin, 					//Monitor pin where LED is attached to show/flash in snyc with signal.
												//Set to -1 if you don't want to use a monitor pin
			bool dcfSignalInverted = false, 	//true, if "original" DCF signal is attached to <DCF77Pin>, false inverted signal is provided
			void (*logCallBack)(String)=NULL	//callback function to log debug messages of DCF decoder (might be NULL if no logging required)
			);
	void start(void (*onTimeDecodedCallback)(dcfTime time) = NULL);
	virtual ~DCFTBL();
	dcfTime getTime(void);						//Last decoded time, please check dcfTime->signalQuality if result is valid.

private:
	int dCFInterrupt;
	static int dCF77Pin;
	static int dCFMonitorPin;
	static bool dcfSignalIsInverted;
	static dcfBit *dcfInfoArray;
	static dcfBit lastDcfBit;
	static unsigned long lastFallingTime;
	static unsigned long lastGoodMinute;
	static unsigned long lastGoodSecond;
	static dcfTime time;

	static void interruptHandler(void);
	static void interruptHandlerRising(void);
	static void interruptHandlerFalling(void);
	static void clearData(void);
	static void decodeTime(void);
	static int decodeNumber(int startidx, int bits);
	static void log(String msg);
	static void (*logger)(String s); //callback function for logging purpose
	static void (*onTimeDecoded)(dcfTime time);
};

} // Namespace TBL
#endif /* DUMMY_H_ */

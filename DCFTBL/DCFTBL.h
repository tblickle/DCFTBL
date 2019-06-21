/*
 * Dummy.h
 *
 *  Created on: 06.04.2019
 *      Author: Tobias
 */
#include <Arduino.h>
#ifndef DCFTBL_H_
#define DCFTBL_H_

#define PULSEWIDTHTOLERANCE 15
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
	DCFTBL(int DCF77Pin, int DCFMonitorPin,void (*logCallBack)(String)=NULL);
	//void start(void (*onTimeDecoded)(dcfTime time)=NULL);
	void start(void (*onTimeDecodedCallback)(dcfTime time) = NULL);
	virtual ~DCFTBL();
	dcfTime getTime(void);
private:
	int dCFInterrupt;
	static int dCF77Pin;
	static int dCFMonitorPin;
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

#endif /* DUMMY_H_ */

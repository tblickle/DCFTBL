/*
 * DCFClockBuffered.cpp
 *
 *  Created on: 20.06.2019
 *      Author: Tobias
 */

#include "DCFClockBuffered.h"

namespace TBL {

// Need this static stuff, because callback does not work on objects, only functions
DCFClockBuffered* singleton = NULL;
void decodeCallBack(dcfTime time) {
	if (singleton != NULL) {
		singleton->onTimeDecodedCallback(time);
	}
}

DCFClockBuffered::DCFClockBuffered(int DCF77Pin, int DCFMonitorPin, bool dcfSignalInverted, void (*logCallBack)(String)) {

	dcf = new DCFTBL(DCF77Pin,DCFMonitorPin,dcfSignalInverted,logCallBack);
	clock = new Clock();
	dcf->start(decodeCallBack);
	singleton = this;
	logger = logCallBack;
}

void DCFClockBuffered::onTimeDecodedCallback(dcfTime time) {
	// Called by DCFTBL when minute signal is detected on DCF
	if (time.hour>=0 && time.minute>=0) {
		//positive values mean valid decoding
		setTime(Time(time.hour, time.minute, 0));
		lastDecodedTime = time;
		log("Decoded time: "+String(time.hour)+":"+String(time.minute));
	} else {
		clock->syncMinute();
	}
}

Time DCFClockBuffered::getTime() {
	return clock->getTime();
}

void DCFClockBuffered::setTime(Time currentTime) {
	clock->setTime(currentTime);
}

int DCFClockBuffered::getQuality() {
	return dcf->getTime().signalQuality;
}

dcfTime DCFClockBuffered::getLastDecodedTime() {
	return lastDecodedTime;
}

void DCFClockBuffered::log(String msg) {
	if (logger != NULL) {
		logger("DCF77ClockBuffered: "+msg);
	}
}

} /* namespace TBL */

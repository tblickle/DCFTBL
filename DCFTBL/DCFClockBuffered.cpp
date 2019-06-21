/*
 * DCFClockBuffered.cpp
 *
 *  Created on: 20.06.2019
 *      Author: Tobias
 */

#include "DCFClockBuffered.h"

namespace TBL {

DCFClockBuffered* singleton = NULL;
void decodeCallBack(dcfTime time) {
	if (singleton != NULL) {
		singleton->onTimeDecodedCallback(time);
	}
}

DCFClockBuffered::DCFClockBuffered(int DCF77Pin, int DCFMonitorPin,void (*logCallBack)(String)) {

	dcf = new DCFTBL(DCF77Pin,DCFMonitorPin,logCallBack);
	clock = new Clock();
	dcf->start(decodeCallBack);
	quality = 0;
	singleton = this;
}

void DCFClockBuffered::onTimeDecodedCallback(dcfTime time) {
	clock->resetTime(Time(time.hour, time.minute));
	quality = time.signalQuality;
	lastDecodedTime = time;
}

Time DCFClockBuffered::getTime() {
	return clock->getTime();
}

int DCFClockBuffered::getQuality() {
	return quality;
}

dcfTime DCFClockBuffered::getLastDecodedTime() {
	return lastDecodedTime;
}

} /* namespace TBL */

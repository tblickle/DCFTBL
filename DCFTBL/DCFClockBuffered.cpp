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

DCFClockBuffered::DCFClockBuffered(int DCF77Pin, int DCFMonitorPin, bool dcfSignalInverted, void (*logCallBack)(String)) {

	dcf = new DCFTBL(DCF77Pin,DCFMonitorPin,dcfSignalInverted,logCallBack);
	clock = new Clock();
	dcf->start(decodeCallBack);
	quality = 0;
	singleton = this;
}

void DCFClockBuffered::onTimeDecodedCallback(dcfTime time) {
	quality = time.signalQuality;
	if (quality == 100) {
		clock->resetTime(Time(time.hour, time.minute, 0));
		lastDecodedTime = time;
	} else {
		clock->syncMinute();
	}

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

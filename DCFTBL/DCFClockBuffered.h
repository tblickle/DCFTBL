/*
 * DCFClockBuffered.h
 *
 *  Created on: 20.06.2019
 *      Author: Tobias
 */

#ifndef DCFCLOCKBUFFERED_H_
#define DCFCLOCKBUFFERED_H_

#include "Clock.h"
#include "DCFTBL.h"

namespace TBL {

class DCFClockBuffered {
public:
	DCFClockBuffered(int DCF77Pin, int DCFMonitorPin,void (*logCallBack)(String)=NULL);
	Time getTime();
	int getQuality();
	dcfTime getLastDecodedTime();
	void onTimeDecodedCallback(dcfTime time);

private:
	DCFTBL* dcf;
	Clock* clock;
	dcfTime lastDecodedTime;
	int quality;
};

} /* namespace TBL */

#endif /* DCFCLOCKBUFFERED_H_ */

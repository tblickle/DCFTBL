/*
 * DCFClockBuffered.h
 *
 * Buffered DCF Clock: Uses DCFTBL class to decode DCF 77 signal. Sets/adjusts the internal clock each time the DCF time has been decoded
 * successfully. Keeps internal track of the time, even if no signal is received for a longer period of time
 * Just call <getTime()> and the most know accurate time will be returned
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
	// Ctor, see <DCFTBL.h>
	DCFClockBuffered(int DCF77Pin, int DCFMonitorPin, bool dcfSignalInverted=false, void (*logCallBack)(String)=NULL);

	Time getTime(); // returns current most accurate time
	void setTime(Time currentTime);
	int getQuality(); // returns quality of last decoded signal (0-100). Indication of quality of receiver
	dcfTime getLastDecodedTime(); // return the last successfully decoded signal (as <dcfTime>). Might be quiet different from <getTime()>
	void onTimeDecodedCallback(dcfTime time); // internal callback, not API

private:
	DCFTBL* dcf;
	Clock* clock;
	dcfTime lastDecodedTime;
	void (*logger)(String s); //callback function for logging purpose
	void log(String msg);
};

} /* namespace TBL */

#endif /* DCFCLOCKBUFFERED_H_ */

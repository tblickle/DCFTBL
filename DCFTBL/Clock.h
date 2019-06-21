/*
 * Clock.h
 *
 * A clock computes the time of the day based on millis()
 * The moment you create the Clock or call <resetTime> the time is set to the passed time stamp
 *  Created on: 19.06.2019
 *      Author: Tobias
 */
#include <Arduino.h>

#include "Time.h"
#ifndef TBL_CLOCK_H_
#define TBL_CLOCK_H_

namespace TBL {

class Clock {
public:
	Clock(TBL::Time currentTime = Time());
	TBL::Time getTime();
	void resetTime(TBL::Time currentTime);

private:
	unsigned long startMillis;
	TBL::Time startTime;
	void recomputeTime();

};

} /* namespace TBL */

#endif /* TBL_CLOCK_H_ */

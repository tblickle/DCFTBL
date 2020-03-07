/*
 * Clock.cpp
 *
 *  Created on: 19.06.2019
 *      Author: Tobias
 */

#include "Clock.h"

#define MINUTE 60
#define HOUR 3600
#define DAY 86400

namespace TBL {

Clock::Clock(TBL::Time currentTime) {
	setTime(currentTime);
}


void Clock::setTime(TBL::Time currentTime) {
	startTime = currentTime;
	startMillis = millis();
}


TBL::Time Clock::getTime() {
	recomputeTime();
	return startTime;
}

void Clock::syncMinute() {
	int hour = startTime.getHour();
	int minute = startTime.getMinute();
	if (startTime.getSecond()<30) {
		setTime(Time(hour, minute,0));
	} else {
		minute++;
		if (minute>=60) {
			hour++;
		}
		setTime(Time(hour, minute,0));
	}
}

void Clock::recomputeTime() {
	unsigned long deltaInMillis=millis() - startMillis; // will also work on millis() overflow
	startMillis = millis();

	long milliPlus = deltaInMillis % 1000;
	long deltaInSeconds = deltaInMillis / 1000;
	long relevantSeconds = deltaInSeconds % DAY;
	long secPlus= relevantSeconds % MINUTE;
	long minPlus= (relevantSeconds % HOUR) / MINUTE;
	long hourPlus = relevantSeconds / HOUR;

	long milliNew = (startTime.getMillis() + milliPlus);
	if (milliNew>=1000) {
		secPlus++;
	}

	long secNew = (startTime.getSecond() + secPlus);
	if (secNew>=60) {
		minPlus ++;
	}

	long minNew = (startTime.getMinute() + minPlus);
	if (minNew>=60) {
		hourPlus ++;
	}

	long hourNew = (startTime.getHour() + hourPlus);

	startTime =  TBL::Time(hourNew % 24, minNew % 60, secNew % 60,milliNew % 1000 );
}

} /* namespace TBL */

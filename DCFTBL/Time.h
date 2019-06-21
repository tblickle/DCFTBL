/*
 * Time.h
 *  POCO to hold the time of day
 *  Created on: 20.06.2019
 *      Author: Tobias
 */

#ifndef TBL_TIME_H_
#define TBL_TIME_H_

namespace TBL {

class Time {
public:
	Time();
	Time(short hour, short minute, short second = 0, short millis = 0);
	short getMillis();
	short getSecond();
	short getMinute();
	short getHour();

private:
	short millis;
	short second;
	short minute;
	short hour;
};

} /* namespace TBL */

#endif /* TBL_TIME_H_ */

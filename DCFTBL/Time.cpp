/*
 * Time.cpp
 *
 *  Created on: 20.06.2019
 *      Author: Tobias
 */

#include "Time.h"

namespace TBL {

Time::Time() {
	this->millis = 0;
	this->second = 0;
	this->minute = 0;
	this->hour = 0;
}

Time::Time(short hour, short minute, short second , short millis ) {
	this->millis = millis % 1000;
	this->second = second % 60;
	this->minute = minute %60 ;
	this->hour = hour % 24;
}
short Time::getMillis() {
	return millis;
}
short Time::getSecond() {
	return second;
}
short Time::getMinute() {
	return minute;
}
short Time::getHour() {
	return hour;
}

} /* namespace TBL */

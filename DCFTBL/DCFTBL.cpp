/*
 * Dummy.cpp
 *
 *  Created on: 06.04.2019
 *      Author: Tobias
 */

#include "DCFTBL.h"

namespace TBL {

DCFTBL::DCFTBL(int DCF77Pin, int DCFMonitorPin, bool dcfSignalInverted, void (*logCallBack)(String)) {
	dCF77Pin = DCF77Pin;
	dCFMonitorPin = DCFMonitorPin;
	dcfSignalIsInverted = dcfSignalInverted;
	logger = logCallBack;
	dCFInterrupt = digitalPinToInterrupt(DCF77Pin);
	if (dCFInterrupt == NOT_AN_INTERRUPT) {
		logger("Error: Pin "+String(dCF77Pin)+" does not support interrupts.");
	}
	pinMode(dCF77Pin, INPUT);
	if (dCFMonitorPin>=0) {
		pinMode(dCFMonitorPin,OUTPUT);
	}
	clearData();
}

DCFTBL::~DCFTBL() {

}

dcfTime DCFTBL::getTime() {
	return time;
}

void DCFTBL::interruptHandler() {

		byte sensorValue = digitalRead(dCF77Pin);
		if (dcfSignalIsInverted) {
			sensorValue = !sensorValue;
		}
		if (sensorValue) {
			if (dCFMonitorPin>=0) {
				digitalWrite(dCFMonitorPin, HIGH);
			}
			interruptHandlerRising();
		} else {
			if (dCFMonitorPin>=0) {
				digitalWrite(dCFMonitorPin, LOW);
			}
			interruptHandlerFalling();
		}
}

void DCFTBL::interruptHandlerRising() {
	unsigned long interruptTime = millis();

	long pulseWidth = interruptTime - lastFallingTime;

	if (abs(200-pulseWidth)<PULSEWIDTHTOLERANCE) {
		//good long pulse value = 1
		lastDcfBit.value = 1;
		lastDcfBit.valid = true;
	} else if (abs(100-pulseWidth)<PULSEWIDTHTOLERANCE) {
		//good short pulse value = 0
		lastDcfBit.value = 0;
		lastDcfBit.valid = true;
	} else {
		//noise, something else
		lastDcfBit.value = pulseWidth;
		lastDcfBit.valid = false;
	}

}

void DCFTBL::interruptHandlerFalling() {
	unsigned long interruptTime = millis();
	long lamda = interruptTime - lastFallingTime;
	if (abs(2000-lamda)<MINUTEWIDTHTOLERANCE) {
		// new Minute
		log("Minute start detected. Lambda: "+String(lamda));
		if (lastGoodMinute>0) {
			decodeTime();
		}
		lastGoodMinute = interruptTime;
		clearData();
	} else if (abs(1000-lamda)<SECONDWIDTHTOLERANCE) {
		// good Second
		unsigned long secondGuess = (interruptTime - lastGoodMinute +500 ) / 1000 -1;

		if (secondGuess >=0 && secondGuess <59) {
			dcfInfoArray[secondGuess]=lastDcfBit;
		}

		if  (lastDcfBit.valid) {
			log("Good second.    Guess="+String(secondGuess)+ " Value="+String(lastDcfBit.value)+" Lambda: "+String(lamda));
		} else {
			log("Invalid second. Guess="+String(secondGuess)+ " PW   ="+String(lastDcfBit.value)+" Lambda: "+String(lamda));
		}

	} else {
		// noise, something else...
		log("Noise. Lambda: "+String(lamda));
	}
	lastFallingTime=interruptTime;
}

void DCFTBL::decodeTime(void) {
	//Signal Quality
	time.signalQuality=0;
	for (int i = 0; i<=58; i++) {
		if (dcfInfoArray[i].valid) {
			time.signalQuality++;
		}
	}
	time.signalQuality = time.signalQuality*100 / 58;


	int min = decodeNumber(21,4) + 10 * decodeNumber(25,3);
	time.minute = min; 		// negative means decode error

	int hr = decodeNumber(29,4) + 10 * decodeNumber(33,2);
	time.hour = hr; 		// negative means decode error

	int dayOfWeek = decodeNumber(42,3);
	if (dayOfWeek >= 0 ) {
		time.dayOfWeek=dayOfWeek;
	}

	int day = decodeNumber(36,4) + 10* decodeNumber(40,2);
	if (day >= 0 ) {
		time.day=day;
	}

	int month = decodeNumber(45,4) + 10* decodeNumber(49,1);
	if (month >= 0 ) {
		time.month=month;
	}

	int year = decodeNumber(50,4) + 10* decodeNumber(54,4);
	if (year >= 0 ) {
		time.year=year;
	}
	if (onTimeDecoded != NULL) {
		// notify callback
		onTimeDecoded(time);
	}
}

int DCFTBL::decodeNumber(int startidx, int bits) {
	boolean decodeok = true;
	int val = -1000; // be sure, value remains negative, even if

	for (int i = startidx ; i<startidx+bits;i++) {
		decodeok = decodeok && dcfInfoArray[i].valid;
	}
	if (decodeok) {
		val = 0;
		int mult = 1;
		for (int i=startidx;i<startidx+bits;i++) {
			val = val + dcfInfoArray[i].value * mult;
			mult = mult * 2;
		}
	}
	return val;
}


void DCFTBL::start(void (*onTimeDecodedCallback)(dcfTime time)) {
	onTimeDecoded = onTimeDecodedCallback;
	attachInterrupt(dCFInterrupt, interruptHandler, CHANGE);
}

void DCFTBL::clearData() {
	for (int i=0;i<59;i++) {
			dcfInfoArray[i]={0,false};
		}
}

void DCFTBL::log(String msg) {
	if (logger != NULL) {
			logger("DCF77TBL: "+msg);
		}
}

// all the static init stuff
int DCFTBL::dCF77Pin = 0;
int DCFTBL::dCFMonitorPin=0;
bool DCFTBL::dcfSignalIsInverted = false;
dcfBit *DCFTBL::dcfInfoArray = new dcfBit[59];
dcfBit  DCFTBL::lastDcfBit = {0,false};
unsigned long DCFTBL::lastFallingTime = 0;
unsigned long DCFTBL::lastGoodMinute = 0;
unsigned long DCFTBL::lastGoodSecond = 0;
void (*DCFTBL::logger)(String) = NULL;
void (*DCFTBL::onTimeDecoded)(dcfTime time) = NULL;
dcfTime DCFTBL::time = {0,0,0,0,0,0,0,0};
}

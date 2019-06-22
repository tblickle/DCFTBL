#include <Arduino.h>

#include "DCFClockBuffered.h"

#define DCFPIN 3        // pin where DCF receiver is connected
#define DCF_CTRL_LED 5  // control pin (flashes in sync with DCF signal)

void log(String s) {
  Serial.println(s);
}

TBL::DCFClockBuffered dc = TBL::DCFClockBuffered(DCFPIN,DCF_CTRL_LED,true);

/*
 * All CTor parameters of TBL::DCFClockBuffered(
int DCF77Pin,						//Arduino pin where DCF Receiver is attached
int DCFMonitorPin, 					//Monitor pin where LED is attached to show/flash in snyc with signal.
									//Set to -1 if you don't want to use a monitor pin
bool dcfSignalInverted = false, 	//true, if "original" DCF signal is attached to <DCF77Pin>, false inverted signal is provided
void (*logCallBack)(String)=NULL	//callback function to log debug messages of DCF decoder (might be NULL if no logging required)
)
*/

void setup() {
  Serial.begin(9600);
  Serial.println("DCF started");
}


void loop() {

 TBL::Time ct = dc.getTime();
 Serial.println("Time = "+ String(ct.getHour())+":"+String(ct.getMinute())+":"+String(ct.getSecond()));

 delay(10000);
}

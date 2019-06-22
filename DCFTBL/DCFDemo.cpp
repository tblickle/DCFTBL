#include <Arduino.h>

#include "DCFClockBuffered.h"

#define DCFPIN 3		// pin where DCF receiver is connected
#define DCF_CTRL_LED 5  // control pin (flashes in sync with DCF signal)

void log(String s) {
  Serial.println(s);
}

TBL::DCFClockBuffered dc = TBL::DCFClockBuffered(DCFPIN,DCF_CTRL_LED,true);

//Use the line below instead, if you want to see debug output of DCF receiver
//TBL::DCFClockBuffered dc = TBL::DCFClockBuffered(DCFPIN,DCF_CTRL_LED,true, log);


void setup() {
  Serial.begin(9600);
  Serial.println("DCF started");
}


void loop() {

 Serial.println("Quality = " + String(dc.getQuality()));
 dcfTime time = dc.getLastDecodedTime();
 Serial.println(String(time.day)+"."+String(time.month)+"."+String(time.year)+"   "+ String(time.hour)+":"+String(time.minute)+":"+String(time.second));

 TBL::Time ct = dc.getTime();
 Serial.println("Continued Time = "+ String(ct.getHour())+":"+String(ct.getMinute())+":"+String(ct.getSecond()));

 delay(10000);
}

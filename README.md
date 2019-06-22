# DCFTBL
DCF 77 decoder including buffered clock for Arduino

Easy-to-use DCF decoder that keeps track of current time (based on millis()) even if the signal is lost (for some time).
See the following code example:
```
#include <Arduino.h>
#include "DCFClockBuffered.h"

#define DCFPIN 3        // pin where DCF receiver is connected
#define DCF_CTRL_LED 5  // control pin (flashes in sync with DCF signal)

TBL::DCFClockBuffered dcfClock = TBL::DCFClockBuffered(DCFPIN,DCF_CTRL_LED);

void setup() {
  Serial.begin(9600);
  Serial.println("DCF started");
}

void loop() {
 TBL::Time ct = dcfClock.getTime();  // whereever you want, just call getTime() for the current time
 Serial.println("Continued Time = "+ String(ct.getHour())+":"+String(ct.getMinute())+":"+String(ct.getSecond()));
 delay(10000);
}

```

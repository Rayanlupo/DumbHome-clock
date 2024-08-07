#include <RTClib.h>
#include <TM1637.h>
RTC_DS1307 rtc;
TM1637 display(27, 14); 
int buttonPin = 35;
int hours;
int minutes;
void setup() {
  Serial.begin(115200);
  rtc.begin();
  display.set(); 
  display.init(); 
   if (rtc.begin() = false) {
    Serial.println("Couldn't find RTC");
  }
  if (rtc.isrunning() == false) {
    Serial.println("RTC is NOT running!");
  }

}

void loop() {
DateTime now = rtc.now();
hours = (now.hour(), DEC);
int minutes = (now.minute(), DEC);
Serial.print(hours);
Serial.print(":");
Serial.print(minutes);
time = hours * 100 + minutes;
tm.display(time);
delay(1000);


}

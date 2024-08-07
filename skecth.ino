#include <Wire.h>
#include <RTClib.h>
#include <TM1637.h>

RTC_DS1307 rtc;
TM1637 display(27, 14);

int hours;
int minutes;

void setup() {
  Serial.begin(115200);
  Wire.begin(19, 18); 
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1); 
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  
  }
  display.init();
  display.set(7);  
}

void loop() {
  DateTime now = rtc.now();  
  hours = now.hour();
  minutes = now.minute();  
  displayTime(hours, minutes);
  delay(1000);
}

void displayTime(int hours, int minutes) {
  int8_t displayData[4];
  displayData[0] = hours / 10;  
  displayData[1] = hours % 10;  
  displayData[2] = minutes / 10;  
  displayData[3] = minutes % 10; 
  display.display(displayData);
}

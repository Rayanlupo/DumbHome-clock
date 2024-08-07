#include <RTClib.h>
#include <TM1637.h>
RTC_DS1307 rtc;
TM1637 display(27, 14); 
int buttonPin = 35;
int hours;
int minutes;
int show;
int on;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  rtc.begin();
  display.set(); 
  display.init(); 
   if (!rtc.begin()) {
    Serial.println("RTC not found");
  }
  if (rtc.isrunning() == false) {
    Serial.println("RTC is not running");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  }
  display.set(7);


}

void loop() {

DateTime now = rtc.now();
hours = (now.hour());
int minutes = (now.minute());
Serial.print(hours);
Serial.print(":");
Serial.print(minutes);
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


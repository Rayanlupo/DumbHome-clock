#include <Wire.h>
#include <RTClib.h>
#include <TM1637.h>

RTC_DS1307 rtc;
TM1637 display(27, 14);

const int buttonPin = 34;  
bool lastButtonState = HIGH;
bool currentButtonState = HIGH;
unsigned long lastDebounceTime = 0;  
const unsigned long debounceDelay = 50;  
unsigned long buttonPressTime = 0;
const unsigned long displayDuration = 10000;  
bool displayOn = false;
void setup() {
  Serial.begin(115200);
  Wire.begin(19, 18);  
  
  pinMode(buttonPin, INPUT_PULLUP); 

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
  int buttonState = digitalRead(buttonPin);  

  if (buttonState != lastButtonState) {
    lastDebounceTime = millis();  
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (buttonState != currentButtonState) {
      currentButtonState = buttonState;
      
      if (currentButtonState == LOW) {
        DateTime now = rtc.now();  
        int hours = now.hour();
        int minutes = now.minute();  
        displayTime(hours, minutes);
        displayOn = true;
      }

    }
  }

  lastButtonState = buttonState;  

   if (displayOn && (millis() - buttonPressTime >= displayDuration)) {
    displayOn = false; 
    clearDisplay();
}
}
void displayTime(int hours, int minutes) {
  int8_t displayData[4];
  

  displayData[0] = hours / 10;  
  displayData[1] = hours % 10;  
  displayData[2] = minutes / 10;  
  displayData[3] = minutes % 10; 

  display.display(displayData);
}
void clearDisplay() {
  int8_t clearData[4] = { 0x7F, 0x7F, 0x7F, 0x7F }; 
  display.display(clearData);
}

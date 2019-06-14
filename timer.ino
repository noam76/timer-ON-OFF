#include <Wire.h>
#include "DS3231.h"
RTClib RTC;

int Relay = 4;
const int OnHour = 12;
const int OnMin = 24;
const int OffHour = 12;
const int OffMin = 25;

void setup () {
    Serial.begin(57600);
    Wire.begin();
    pinMode(Relay, OUTPUT);
    digitalWrite(Relay, LOW);
}

void loop() {
  delay(1000);

  DateTime now = RTC.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  
 if(now.hour() == OnHour && now.minute() == OnMin){
    digitalWrite(Relay,HIGH);
    Serial.println("LIGHT ON");
    }
    
    else if(now.hour() == OffHour && now.minute() == OffMin){
      digitalWrite(Relay,LOW);
      Serial.println("LIGHT OFF");
    }
}

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//int LED1 = 12;
//int LED2 = 13;
// Set Buttons 
int set = 3;
int up = 4;
int down = 5;

int time1 = 0;
// Read the status of the buttons
int buttonUpState = 0;
int buttonDownState = 0;
// 
int prevBtnUp = LOW;
int prevBtnDwn = LOW;
unsigned long lastBtnUp = 0;
unsigned long lastBtnDwn = 0;
int transInt = 50;

//boolean LED1State = false;
//boolean LED2State = false;
// long press 
long buttonTimer = 0;
long longPressTime = 300;
boolean buttonActive = false;
boolean longPressActive = false;
boolean setActive = false;

// set the lcd
//U8G2_HX1230_96X68_F_3W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* reset=*/ 8);
U8G2_HX1230_96X68_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

void setup() {
 u8g2.begin();
 u8g2.enableUTF8Print();    // enable UTF8 support for the Arduino print() function
 //pinMode(LED1, OUTPUT);
 //pinMode(LED2, OUTPUT);
 pinMode(set, INPUT);
 pinMode(up, INPUT);
 pinMode(down, INPUT);
}

void loop() {
 u8g2.setFont(u8g2_font_unifont_t_hebrew);  // use chinese2 for all the glyphs of "你好世界"
 u8g2.setFontDirection(0);
 u8g2.clearBuffer();
 u8g2.setCursor(0, 15);
 u8g2.print("Hello World!");
 u8g2.setCursor(0, 40);
 u8g2.print("שלום");    // Hebrew "Hello World"
 u8g2.sendBuffer();
  
 delay(1000);
  
 if (digitalRead(set) == HIGH) {
   if (buttonActive == false) {
     buttonActive = true;
     buttonTimer = millis();
     }
    if ((millis() - buttonTimer > longPressTime) && (longPressActive == false)) {
      longPressActive = true;
      setActive = !setActive;
      //LED1State = !LED1State;
      //digitalWrite(LED1, LED1State);
    }
  } else {
    if (buttonActive == true) {
      if (longPressActive == true) {
        longPressActive = false;
      } else {
        //LED2State = !LED2State;
        //digitalWrite(LED2, LED2State);
      }
      buttonActive = false;
    }
  }
  if(setActive == true){
    buttonUpState = digitalRead(up);
    buttonDownState = digitalRead(down);
    if (buttonUpState == HIGH && prevBtnUp == LOW){
      if (millis() - lastBtnUp > transInt){
        time1++;
        if (time1 > 9){
          time1 = 0;
        }
        lastBtnUp = millis();
        Serial.println(time1);
      }
    }
    prevBtnUp = buttonUpState;

    if (buttonDownState == HIGH && prevBtnDwn == LOW){
      if(millis() - lastBtnDwn > transInt){
        time1--;
        if (time1 < 0){
          time1 = 9;
        }
        lastBtnDwn = millis();
        Serial.println(time1);
      }
    }
    prevBtnDwn = buttonDownState;
  }
}

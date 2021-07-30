//SDA-A4
//SCL-A5
#define BTN1 2
#define BTN2 3
#include "GyverButton.h"
GButton butt1(BTN1); 
GButton butt2(BTN2);

#include <OLED_I2C.h>
OLED  myOLED(SDA, SCL, 8);
extern uint8_t SmallFont[];

#include <DS3231.h>
DS3231  rtc(SDA, SCL);

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme;
unsigned long delayTime;

int i=0;
String text1;

void setup() {
  myOLED.begin();
  myOLED.setFont(SmallFont);
  rtc.begin();
  unsigned status;
  status = bme.begin(); 
}
void loop() {
  butt1.tick();
  butt2.tick();
  if (i<0) i=0;
  if (i>3) i=0;
  if (butt1.isClick()) i=i+1 ;
  if (butt2.isClick()) i=i-1 ;
    myOLED.printNumI(i,RIGHT,65);
    myOLED.update();
    if(i==0){
      myOLED.clrScr();
      myOLED.print(rtc.getTimeStr(),CENTER,20);
      text1="t="+String(bme.readTemperature())+"*C";
      myOLED.print(text1,CENTER,30);
    }
    if(i==1){
      myOLED.clrScr();
      myOLED.print(rtc.getDOWStr(),CENTER,10);
      myOLED.print(rtc.getDateStr(),CENTER,20);
      myOLED.print(rtc.getTimeStr(),CENTER,30);
      text1="t="+String(rtc.getTemp())+"*C";
      myOLED.print(text1,CENTER,40);
    }
    if(i==2){
      myOLED.clrScr();
      text1="t="+String(bme.readTemperature())+"*C";
      myOLED.print(text1,CENTER,10);
      text1="p="+String(bme.readPressure()/133.32)+"mm.rt.st";
      myOLED.print(text1,CENTER,20);
      text1="h="+String(bme.readAltitude(SEALEVELPRESSURE_HPA))+"m";
      myOLED.print(text1,CENTER,30);
      text1="v="+String(bme.readHumidity())+"%";
      myOLED.print(text1,CENTER,40);
    }
    if(i==3){
        myOLED.clrScr();
        for (int p=128; p>=-(34*4); p=p-2){
        myOLED.print("OLED_I2C Scrolling Text Demo ", i, 32);
        myOLED.update();
        }
      }
}

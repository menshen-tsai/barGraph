#include <Arduino.h>
#include <SPI.h>
#include "TFT_eSPI.h"
#include <XPT2046.h>
#include "TimeLib.h"
#include <BarGraph.h>


// Color Pallette

#define BACKCOLOR TFT_BLACK     //0x18E3
#define OFFSET 120


XPT2046 touch(/*cs=*/ 4, /*irq=*/ 5);
// Use hardware SPI
TFT_eSPI tft = TFT_eSPI();

//Analog Measurement Declarations
const int analogIn = A0;
int RawValue = 0;
int LastPercent = 0;

time_t new_second, old_second;

BarGraph bar0, bar1, bar2, bar3;



void setup() {
    int retry=0;  

  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println();
  Serial.print(__FILE__);
  Serial.print(" compiled at ");
  Serial.print(__DATE__);Serial.print(" ");Serial.println(__TIME__);

  tft.begin();
  tft.fillScreen(BACKCOLOR);

  bar0.begin(0, 100,  47,         20, tft);
  bar1.begin(0, 100,  47+OFFSET,  20, tft);
  bar2.begin(0, 100,  47,        180, tft);
  bar3.begin(950, 1050, 47+OFFSET, 180, tft);

  bar1.setColor(TFT_YELLOW, BACKCOLOR);
  bar2.setColor(TFT_BLUE,   BACKCOLOR);
  
  bar0.drawScale(); 
  bar1.drawScale();
  bar2.drawScale();
  bar3.drawScale();
    
}

void loop(){  
  char buf[20];
  char buf_t[8];
  float newPercent;

  if (old_second != second()) {
    old_second = second();

    RawValue = analogRead(analogIn);
    newPercent = int((RawValue/1024.0)* 100.0);
    
    bar0.drawBar((int)newPercent);     
    bar0.drawText(RawValue, 3);

    RawValue = analogRead(analogIn)*2;
    if (RawValue > 1023)
       RawValue = 1023;
    newPercent = int((RawValue/1024.0)* 100.0);
    bar1.drawBar((int)newPercent);     
    bar1.drawText(RawValue, 2);

    RawValue = analogRead(analogIn)*3;
    if (RawValue > 1023)
       RawValue = 1023;
    newPercent = int((RawValue/1024.0)* 100.0);
    bar2.drawBar((int)newPercent);     
    bar2.drawText(RawValue, 1);

    RawValue = analogRead(analogIn)*4;
    if (RawValue > 1023)
       RawValue = 1023;
    newPercent = int((RawValue/1024.0)* 100.0);
    bar3.drawBar((int)newPercent);     
    // Maps 0~1023 to 950~1050
    bar3.drawText(RawValue*100.0/1023.0+950.0, 0);

  
  }
}
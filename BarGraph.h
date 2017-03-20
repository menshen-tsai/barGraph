
#ifndef _BarGraphH_
#define _BarGraphH_

#include "TFT_eSPI.h"
#include <Arduino.h>

#define SCALECOLOR 0xFFFF

class BarGraph
{
  public:
    BarGraph();
	void begin(int l, int u, int x, int y, TFT_eSPI& tft);
	void setColor(int bar, int back);
    void drawBar(int nPer);
	void drawScale();
	void drawText(String s) ;
	void drawText(char* s) ;
	void drawText(int v) ;
	void drawText(float v, int p) ;
  private:
     int _lastPercent;
	 int _upper;
	 int _lower;
	 int _barColor;
	 int _backColor;
	 int _x;
	 int _y;
	 TFT_eSPI _tft;
};

#endif
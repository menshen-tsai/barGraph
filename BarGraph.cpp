// Code is based on http://henrysbench.capnfatz.com/henrys-bench/arduino-adafruit-gfx-library-user-guide/arduino-adafruit-gfx-bar-graph/

#include <BarGraph.h>

BarGraph::BarGraph() {
}

void BarGraph::begin(int l, int u, int x, int y, TFT_eSPI& tft) {
	this->_lastPercent = 0;
	this->_upper = u;
	this->_lower = l;
	this->_x = x;
	this->_y = y;
	this->_tft = tft;
	this->_barColor = TFT_GREEN;
	this->_backColor = TFT_BLACK;
}

void BarGraph::setColor(int bar, int back){
    this->_barColor = bar;
	this->_backColor = back;
}

void BarGraph::drawBar (int nPer){
  if (abs(nPer - _lastPercent) < 1) return;
  if(nPer < _lastPercent){
//    _tft.fillRect(61+i*OFFSET, 20 + (100-_lastPercent), 30, _lastPercent - nPer,  BACKCOLOR);     
    _tft.fillRect(_x+14, _y + (100-_lastPercent), 30, _lastPercent - nPer,  _backColor);     	
  }
  else{
//    _tft.fillRect(61+i*OFFSET, 20 + (100-nPer), 30, nPer - _lastPercent,  BARCOLOR);
    _tft.fillRect(_x+14, _y + (100-nPer), 30, nPer - _lastPercent,  _barColor);	
  }    
  _lastPercent = nPer;  
  
}


void BarGraph::drawScale(){
  char buf[10];
  int ind, tick;
//  _tft.drawFastVLine(55+i*OFFSET, 20,100, SCALECOLOR ); // Vertical Scale Line  
//  _tft.drawFastHLine(47+i*OFFSET, 20, 8, SCALECOLOR); // Major Division
//  _tft.drawFastHLine(50+i*OFFSET, 44, 5, SCALECOLOR); // Minor Division
//  _tft.drawFastHLine(47+i*OFFSET, 69, 8, SCALECOLOR); // Major Division
// _tft.drawFastHLine(50+i*OFFSET, 94, 5, SCALECOLOR); // Minor Division
//  _tft.drawFastHLine(47+i*OFFSET, 119, 8, SCALECOLOR);  // Major Division

  _tft.drawFastVLine(_x+8, _y,    100, SCALECOLOR);
  _tft.drawFastHLine(_x,   _y,    8,   SCALECOLOR);
  _tft.drawFastHLine(_x+3, _y+24, 5,   SCALECOLOR);
  _tft.drawFastHLine(_x,   _y+49, 8,   SCALECOLOR);
  _tft.drawFastHLine(_x+3, _y+74, 5,   SCALECOLOR);
  _tft.drawFastHLine(_x,   _y+99, 8,   SCALECOLOR);
   
  _tft.setTextSize(1);
  for(ind=0; ind<5; ind++) {
    tick=_upper-ind*(_upper-_lower)/4;
    sprintf(buf, "%d", tick);
      _tft.drawRightString(buf,_x+3,_y-5+ind*25,1);
//    tft.drawCentreString("40",30+i*OFFSET,15,1);
//    tft.drawCentreString("30" ,30+i*OFFSET,39,1);
//    tft.drawCentreString("20" ,30+i*OFFSET,64,1);  
//    tft.drawCentreString("10" ,30+i*OFFSET,89,1);  
//    tft.drawCentreString("0"  ,30+i*OFFSET,114,1);
  }
}

void BarGraph::drawText(String s) {
  char buf_t[20];
  
  s.toCharArray(buf_t, 20);  
  _tft.setTextSize(1);
  _tft.drawCentreString(buf_t,_x+8,_y+110,1);
}

void BarGraph::drawText(char* s) {
  _tft.setTextSize(1);
  _tft.drawCentreString(s,_x+8,_y+110,1);
}

void BarGraph::drawText(int v) {
  char buf_t[20];
  
  sprintf(buf_t, "%d", v);
  _tft.setTextSize(1);
  _tft.drawCentreString(buf_t,_x+8,_y+110,1);
}

void BarGraph::drawText(float v, int p) {
  char buf_t[10];
  /* 4 is mininum width, p is precision; float value is copied onto buf_t*/
  dtostrf(v, 4, p, buf_t);
  _tft.setTextSize(1);
  _tft.drawCentreString(buf_t,_x+8,_y+110,1);
}



#include"LedControl.h"

LedControl lc=LedControl(12,11,10,1);
unsigned long delayTime=100;

byte si[]=
{
  B00011000,
  B00111100,
  B01111110,
  B11011011,
  B11111111,
  B00100100,
  B01011010,
  B10100101
  };


 void setup()
 {
  lc.shutdown(0,false);
  lc.setIntensity(0,0);
  lc.clearDisplay(0);
  
 }

 void spaceInvader()
 {
  for(int i=0;i<8;i++)
  {
    lc.setRow(0,i,si[i]);
  }
 }

 void loop()
 {
  spaceInvader();
  for(int j=0;j<9;j++)
  {
    lc.setIntensity(0,j);
    delay(delayTime);
  }
 }


#include<LedControl.h>

LedControl lc=LedControl(12,11,10,1);
unsigned long delayTime=100;

byte si[]  =
{
B00000000,
B00000000,
B01000010,
B00000000,
B00000000,
B01111110,
B00111100,
B00000000
};


byte so[] =
{
B00000000,
B00000000,
B10000100,
B00000000,
B00000000,
B01111110,
B00111100,
B00000000
};
 void setup()
 {
  lc.shutdown(0,false);
  lc.setIntensity(0,0);
  lc.clearDisplay(0);
   }

 void face()
 {
  for(int i=0;i<8;i++)
  {
    lc.setRow(0,i,si[i]);
  }
 }

 void loop()
 {
  face();
  for(int j=0;j<9;j++)
  {
    lc.setIntensity(0,j);
    delay(delayTime);
  }
 }


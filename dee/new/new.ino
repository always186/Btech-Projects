#include "LedControl"

LedControl lc=LedControl(12,11,10,2);  //pin and # of displays
unsigned long delayTime=200;   //time between frames

//put value in arrays

byte invaderla[]  =
{
  
  B00011000,               //first frame of invader #1
  B00111100,
  B01111110,
  B11011011,
  B11111111,
  B00100100,
  B01011010,
  B10100101
};

byte invaderlb[]   =
{
  B00011000,
  B00111100,
  B01111110,
  B11011011,
  B11111111,
  B00100100,
  B01011010,
  B01000010
};

byte invader2a[]   =
{
  B00100100,
  B00100100,
  B01111110,
  B11011011,
  B11111111,
  B11111111,
  B10100101,
  B00100100
 };

 byte invader2b[]   =
{
  B00100100,
  B10100101,
  B11111111,
  B11011011,
  B11111111,
  B01111110,
  B00100100,
  B01000010
 };
void setup() {
  // put your setup code here, to run once:
lc.shutdown(0,false);
lc.shutdown(1,false);
lc.setIntensity(0,5);
lc.setIntensity(1,5);
lc.clearDisplay(0);
lc.clearDisplay(1);
}

//take values in array and display then on displays
void sinvaderla()
{
  for(int i=0; i<8; i++)
  {
    lc.setRow(0,i,invaderla[i]);
  }
  }
  void sinvaderlb()
  {
    for(int i=0; i<8;i++)
    {
      lc.setRow(0,i,invaderlb[i]);
    }
  }

  void sinvader2a()
  {
    for(int i=0; i<8;i++)
    {
      lc.setRow(1,i,invader2a[i]);
    }
  }

  void sinvader2b()
  {
    for(int i=0; i<8;i++)
    {
      lc.setRow(1,i,invader2b[i]);
    }
  }
void loop() {
//put #1 frame display
 sinvaderla();
 delay(delayTime);
 sinvader2a();
 delay(delayTime);   

//put #2 frame display
 sinvaderlb();
 delay(delayTime);
 sinvader2b();
 delay(delayTime);  
}

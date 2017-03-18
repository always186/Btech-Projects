#include <LedControl.h>


LedControl lc=LedControl(12,11,10,1);
unsigned long delayTime=100;

void setup(){
 lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,15);      // Set the brightness to maximum value
 lc.clearDisplay(0);         // and clear the display
}

void loop(){ 

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(1,2);
//Servo servo1;
//Servo servo2;

int accelero; 

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
BTSerial.setTimeout(5);
Serial.setTimeout(5);
//servo1.attach(9);                                  // servo1 on pin9
 //servo2.attach(10);                                 // servo2 on pin10
}


  void loop()
{
  if (BTSerial.available()>0)
  {
   accelero = BTSerial.parseInt();
   accelero = map(accelero, 0, 500, 0, 2000);
   Serial.println(accelero);
   delay(1000);
  /* if(accelero>3000 &&  accelero<4000 )
   {
   accelero=accelero-3000;
   accelero = map(accelero, 0, 100, 1500, 2000);// mapping the servo2 received value and position range
   Serial.println("1:::::");
   Serial.println(accelero);
   }*/
  /* else if(accelero >-30,000 && accelero<0)
   {// delay(1000);
    accelero = map(accelero, -30000, 0, 0, 1500);
    Serial.println("2-----");
    Serial.println(accelero);
   }*/
  }
  
}



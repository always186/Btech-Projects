//#include <Servo.h> 
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
 // servo2.attach(10);                                 // servo2 on pin10
}

void loop()
{
  if (BTSerial.available()>0)
  {
    accelero = BTSerial.parseInt();
     accelero = map(accelero, 0, 500, 0, 2000);   // mapping the servo2 received value and position range
     Serial.println(accelero);
  }
}

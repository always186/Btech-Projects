#include <SoftwareSerial.h>

#include <Servo.h> 
SoftwareSerial BTSerial(1,2);
//Servo servo1;
//Servo servo2;

float accelero; 

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
 // Serial.setTimeout(5);
//servo1.attach(9);                                  // servo1 on pin9
 //servo2.attach(10);                                 // servo2 on pin10
}

void loop()
{
  while (BTSerial.available())
  {
   // accelero = BTSerial.read();
   // Serial.println(accelero);
    Serial.println((float)BTSerial.read());
    
   // delay(500);
  }
}


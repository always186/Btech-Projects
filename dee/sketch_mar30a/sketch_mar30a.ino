#include <Keyboard.h>

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
   accelero = abs(BTSerial.parseInt());
  // accelero = map(accelero, 0, 30000, 0, 1000);
  // accelero = constrain(accelero,0,2000);
 /*  if(accelero<=320 && accelero>0)
   {Keyboard.press(char(KEY_LEFT_ARROW));
   Keyboard.press(char(KEY_UP_ARROW));
   Serial.println("left");
   delay(1000);
   }

   if(accelero>=500 && accelero<800)
   {Keyboard.press(char(KEY_RIGHT_ARROW));
   Keyboard.press(char(KEY_UP_ARROW));
   Serial.println("right");
   delay(1000);
   }
   */
   
   Serial.println(accelero);
   delay(1000);

  }
  
}



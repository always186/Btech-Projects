#include <SoftwareSerial.h>
SoftwareSerial BTSerial(1,2);
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
   accelero = map(accelero, 0, 100, 1500, 2000);
   Serial.println(accelero);
//   delay(1000);

        if(accelero<320 && accelero>=0)
        {
          Keyboard.press(char(KEY_UP_ARROW));
          Keyboard.press(char(KEY_LEFT_ARROW));
          delay(1000);
          
          }
        if(accelero<800 && accelero>=500)
        {
          Keyboard.press(char(KEY_UP_ARROW));
          Keyboard.press(char(KEY_RIGHT_ARROW));
          delay(1000);
          
          } 
         if(accelero>=320 && accelero<500)
         {
                    Keyboard.press(char(KEY_UP_ARROW));
                    delay(1000);

          }
         
  
  }
  
}



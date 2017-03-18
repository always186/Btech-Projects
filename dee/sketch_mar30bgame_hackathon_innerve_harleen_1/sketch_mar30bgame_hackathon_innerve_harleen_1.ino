#include <Keyboard.h>

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
  if(accelero<800)  
   {  Serial.println(accelero);
    if(accelero>=180 && accelero<=280)
   {Serial.println("lrft");
   Keyboard.press(char(KEY_LEFT_ARROW));
   delay(10);
   Keyboard.releaseAll();
   }
   if(accelero>=400 && accelero<=500)
   {Serial.println("right");
      Keyboard.press(char(KEY_RIGHT_ARROW));
      delay(10);
      Keyboard.releaseAll();}

   if(accelero>280 && accelero<400)
   {Serial.println("forward");
      Keyboard.press(char(KEY_UP_ARROW));
      delay(10);
      Keyboard.releaseAll();}


   delay(10);
   
  }
  }
}


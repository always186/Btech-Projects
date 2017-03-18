#include <Keyboard.h>

#include <HID.h>

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(1, 2);

void setup() {
    Serial.begin(9600);
  BTSerial.begin(9600);
  BTSerial.setTimeout(5);
Serial.setTimeout(5);
  //Keyboard.begin();
  // put your setup code here, to run once:

}

void loop() {
  if(BTSerial.available()>0)
{
  
  
  int accelero=Serial.parseInt();
  accelero = map(accelero, 0, 500, 0, 2000); 
  Serial.println(accelero);
  //Serial.println(String(BTSerial.readString()));
  //Serial.println(" ");
 // delay(10);
if(accelero<4000)

  {if(accelero<=320 && accelero>=0);
   
 //  Keyboard.print(char('a'))
  { Keyboard.press(char(KEY_UP_ARROW));
    Keyboard.press(char(KEY_LEFT_ARROW));
    delay(1000);
   
   Keyboard.releaseAll();
   delay(100);}

     if(accelero<=800 && accelero>=500);
   
 //  Keyboard.print(char('a'))
  { Keyboard.press(char(KEY_UP_ARROW));
    Keyboard.press(char(KEY_RIGHT_ARROW));
    delay(1000);
   
   Keyboard.releaseAll();
   delay(100);}

  

  if(accelero<500 && accelero>320);
   
 //  Keyboard.print(char('a'))
  { Keyboard.press(char(KEY_UP_ARROW));
    delay(1000);
   
   Keyboard.releaseAll();
   delay(100);}

  

  }


else if(accelero>4000)
{
  accelero=accelero-4000;
  
    {if(accelero<=320 && accelero>=0);
   
 //  Keyboard.print(char('a'))
  { Keyboard.press(char(KEY_DOWN_ARROW));
    delay(1000);
   
   Keyboard.releaseAll();
   delay(100);}
  
  }

 
  // put your main code here, to run repeatedly:

}
}
}

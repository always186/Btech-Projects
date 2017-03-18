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
  int reading=BTSerial.read();
String readingString = (String)reading;

  
  int accelero=Serial.parseInt();
  accelero = map(accelero, 0, 500, 0, 2000); 
  Serial.println(accelero);
  //Serial.println(String(BTSerial.readString()));
  //Serial.println(" ");
 // delay(10);
if(readingString.charAt(0)=='Y')

  {if(BTSerial.read()<=320 && BTSerial.read()>=0);
   
 //  Keyboard.print(char('a'))
  { Keyboard.press(char(KEY_UP_ARROW));
    Keyboard.press(char(KEY_LEFT_ARROW));
    delay(1000);
   
   Keyboard.releaseAll();
   delay(100);}

     if(BTSerial.read()<=800 && BTSerial.read()>=500);
   
 //  Keyboard.print(char('a'))
  { Keyboard.press(char(KEY_UP_ARROW));
    Keyboard.press(char(KEY_RIGHT_ARROW));
    delay(1000);
   
   Keyboard.releaseAll();
   delay(100);}

  

  if(BTSerial.read()<500 && BTSerial.read()>320);
   
 //  Keyboard.print(char('a'))
  { Keyboard.press(char(KEY_UP_ARROW));
    delay(1000);
   
   Keyboard.releaseAll();
   delay(100);}

  

  }


else if(readingString.charAt(0)=='Z')
{
    {if(BTSerial.read()<=320 && BTSerial.read()>=0);
  
  { Keyboard.press(char(KEY_DOWN_ARROW));
    delay(1000);
   
   Keyboard.releaseAll();
   delay(100);}
  
  }

 
  // put your main code here, to run repeatedly:

}
}
}

#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>
Cytron_PS2Shield ps2(2, 3); // SoftwareSerial: Rx and Tx pin
//Cytron_PS2Shield ps2; // HardwareSerial
void setup()
{
  ps2.begin(9600); 
  Serial.begin(9600);
}

void loop()
{
  if(ps2.readButton(PS2_UP) == 0)
 Serial.println("PS2_UP");
 if(ps2.readButton(PS2_DOWN) == 0)
 Serial.println("PS2_DOWN");
 if(ps2.readButton(PS2_LEFT) == 0)
 Serial.println("PS2_LEFT");
 if(ps2.readButton(PS2_RIGHT) == 0)
 Serial.println("PS2_RIGHT");
 if(ps2.readButton(PS2_SELECT) == 0)
 Serial.println("PS2_SELECT");
 if(ps2.readButton(PS2_START) == 0)
 Serial.println("PS2_START");
 if(ps2.readButton(PS2_TRIANGLE) == 0)
 Serial.println("PS2_TRIANGLE");
 if(ps2.readButton(PS2_CIRCLE) == 0)
 Serial.println("PS2_CIRCLE");
 if(ps2.readButton(PS2_CROSS) == 0)
 Serial.println("PS2_CROSS");
 if(ps2.readButton(PS2_SQUARE) == 0)
 Serial.println("PS2_SQUARE");
 if(ps2.readButton(PS2_LEFT_1) == 0)
 Serial.println("PS2_LEFT_1");
 if(ps2.readButton(PS2_LEFT_2) == 0)
 Serial.println("PS2_LEFT_2");
 if(ps2.readButton(PS2_RIGHT_1) == 0)
 Serial.println("PS2_RIGHT_1");
 if(ps2.readButton(PS2_RIGHT_2) == 0)
 Serial.println("PS2_RIGHT_2");
/* if(ps2.readButton(PS2_JOYSTICK_LEFT_UP) == 0)
 Serial.println("PS2_JOYSTICK_LEFT_UP");
 if(ps2.readButton(PS2_JOYSTICK_RIGHT_UP) == 0)
 Serial.println("PS2_JOYSTICK_RIGHT_UP");
 if(ps2.readButton(PS2_JOYSTICK_LEFT_DOWN) == 0)
 Serial.println("PS2_JOYSTICK_LEFT_DOWN");
 if(ps2.readButton(PS2_JOYSTICK_RIGHT_DOWN) == 0)
 Serial.println("PS2_JOYSTICK_RIGHT_DOWN");
 if(ps2.readButton( PS2_JOYSTICK_LEFT_LEFT) == 0)
 Serial.println(" PS2_JOYSTICK_LEFT_LEFT");
 if(ps2.readButton(PS2_JOYSTICK_RIGHT_LEFT) == 0)
 Serial.println("PS2_JOYSTICK_RIGHT_LEFT");
 if(ps2.readButton(PS2_JOYSTICK_LEFT_RIGHT) == 0)
 Serial.println("PS2_JOYSTICK_LEFT_RIGHT");
 if(ps2.readButton(PS2_JOYSTICK_RIGHT_RIGHT) == 0)
 Serial.println("PS2_JOYSTICK_RIGHT_RIGHT");*/
 if(ps2.readButton(PS2_JOYSTICK_LEFT) == 0){
 Serial.print(ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS));
 Serial.print(" ");
 Serial.println(ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS));
 delay(100);
 }
 if(ps2.readButton(PS2_JOYSTICK_RIGHT) == 0){
 Serial.print(ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS));
 Serial.print(" ");
 Serial.println(ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS));
 delay(100);
 }
}

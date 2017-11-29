#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>

#define mot2a 23
#define mot2b 25
#define mot4a 27
#define mot4b 29
#define am1   31
#define am2   33
#define pc1a 51
#define pc1b 53
#define pc2a 39
#define pc2b 45
#define poleup1 47
#define poleup2 49



Cytron_PS2Shield ps2(10, 11); // SoftwareSerial: Rx and Tx pin
//Cytron_PS2Shield ps2; // HardwareSerial
//shield_ps2(10,11);
#define LEDPIN  13

void setup()
{
  ps2.begin(9600); // This baudrate must same with the jumper setting at PS2 shield
  Serial.begin(9600);

  pinMode(pc1a,OUTPUT);
  pinMode(pc2a,OUTPUT);
  pinMode(pc1b,OUTPUT);
  pinMode(pc2b,OUTPUT);
  pinMode(poleup1,OUTPUT);
  pinMode(poleup2,OUTPUT);
  
}
void loop()
{
  // LED on main board will light up if 'Select' button is pressed
  
 //Serial.println(ps2.getval(PS2_LEFT));
 

   if(ps2.readButton(PS2_DOWN) == 0) // 0 = pressed, 1 = released
  {
    /*digitalWrite(mot2a,HIGH);
    digitalWrite(mot2b,LOW);
    digitalWrite(mot4a,HIGH);
    digitalWrite(mot4b,LOW);

    digitalWrite(LEDPIN, HIGH); */
    //delay(1000);
Serial.println("PS2_DOWN");
  }

  if(ps2.readButton(PS2_UP) == 0) // 0 = pressed, 1 = released
  {
    
   Serial.println("PS2_UP");
    /*digitalWrite(mot2a,LOW);
    digitalWrite(mot2b,HIGH);
    digitalWrite(mot4a,LOW);
    digitalWrite(mot4b,HIGH);
    digitalWrite(LEDPIN,HIGH);*/
  }


 /* if(ps2.readButton(PS2_CIRCLE)==0)
  {
    digitalWrite(mot1a,HIGH);
    digitalWrite(mot1b,LOW);
    digitalWrite(mot2a,HIGH);
    digitalWrite(mot2b,LOW);
    digitalWrite(mot3a,HIGH);
    digitalWrite(mot3b,LOW);
    digitalWrite(mot4a,HIGH);
    digitalWrite(mot4b,LOW); 
    digitalWrite(LEDPIN,HIGH);
  }
*/

 if(ps2.readButton(PS2_SQUARE)==0)//arm upper
    {
      Serial.println("PS2_UP");
   // digitalWrite(am1,HIGH); 
    //digitalWrite(am2,LOW); 
    }

    if(ps2.readButton(PS2_CIRCLE)==0)
   {
    digitalWrite(am1,LOW);
    digitalWrite(am2,HIGH);
   }

  if(ps2.readButton(PS2_TRIANGLE)==0)
  {
    digitalWrite(am1,LOW);
    digitalWrite(am2,LOW);
  }
  if(ps2.readButton(PS2_LEFT_1)==0)//openining of up motor
  {
    digitalWrite(pc1a,HIGH);
    digitalWrite(pc1b,LOW);
  }
  if(ps2.readButton(PS2_LEFT)==0)//closeing of up motor
  {
    digitalWrite(pc1a,LOW);
    digitalWrite(pc1b,HIGH);
  }
   if(ps2.readButton(PS2_RIGHT_1)==0)//opening of down hand
  {
    digitalWrite(pc2a,HIGH);
    digitalWrite(pc2b,LOW);
  }
   if(ps2.readButton(PS2_SQUARE)==0)//closing of down motor
  {
    digitalWrite(pc2a,LOW);
    digitalWrite(pc2b,HIGH);
  }
   
   if(ps2.readButton(PS2_UP)==0)
  {
    digitalWrite(poleup1,HIGH);
    digitalWrite(poleup2,LOW);
  }
   if(ps2.readButton(PS2_DOWN)==0)
  {
    digitalWrite(poleup1,LOW);
    digitalWrite(poleup2,HIGH);
  }
    
   if(ps2.readButton(PS2_CROSS)==0)
  {
    
    digitalWrite(mot2a,LOW);
    digitalWrite(mot2b,LOW);
    digitalWrite(mot4a,LOW);
    digitalWrite(mot4b,LOW); 
    digitalWrite(pc1a,LOW);
     digitalWrite(pc1b,LOW);
     digitalWrite(pc2a,LOW);
     digitalWrite(pc2b,LOW);
     digitalWrite(poleup1,LOW);
     digitalWrite(poleup2,LOW);
    digitalWrite(LEDPIN,HIGH);
  }
  }
   



#include <SoftwareSerial.h>
#include <Cytron_PS2Shield.h>
SoftwareSerial BTSerial(10,11);
Cytron_PS2Shield ps2(10, 11); 
const int led1=2, led2=3,led3=4,led4=5,led5=6,led6=7,led7=8,led8=9,led9=12,led10=13;
void setup()
{
  ps2.begin(9600);
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(led6,OUTPUT);
   pinMode(led7,OUTPUT);
  pinMode(led8,OUTPUT);
  pinMode(led9,OUTPUT);
}
void loop()
{
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  digitalWrite(led5,LOW);
  digitalWrite(led6,LOW);
  digitalWrite(led7,LOW);
  digitalWrite(led8,LOW);
  digitalWrite(led9,LOW);
  digitalWrite(led10,LOW);
   if(ps2.readButton(PS2_DOWN) == 0) 
    digitalWrite(led1,HIGH);
if(ps2.readButton(PS2_UP) == 0) 
    digitalWrite(led2,HIGH);
    if(ps2.readButton(PS2_CIRCLE) == 0) 
    digitalWrite(led3,HIGH);
    if(ps2.readButton(PS2_SQUARE) == 0) 
    digitalWrite(led4,HIGH);
    if(ps2.readButton(PS2_TRIANGLE) == 0) 
    digitalWrite(led5,HIGH);
    if(ps2.readButton(PS2_LEFT) == 0) 
    digitalWrite(led6,HIGH);
    if(ps2.readButton(PS2_LEFT_1) == 0) 
    digitalWrite(led7,HIGH); 
    if(ps2.readButton(PS2_RIGHT_1) == 0) 
    digitalWrite(led8,HIGH); 
   if(ps2.readButton(PS2_RIGHT)==0)
 digitalWrite(led9,HIGH);     
   if(ps2.readButton(PS2_CROSS)==0)
  digitalWrite(led10,HIGH); 
  delay(1000);
  }
   



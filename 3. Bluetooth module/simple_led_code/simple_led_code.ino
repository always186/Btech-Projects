#include<SoftwareSerial.h>
SoftwareSerial bt(0,1);
 int val=0;
const int led=13;
void setup()
{
Serial.begin(9600);
bt.begin(9600);
pinMode(led,OUTPUT);
}
void loop()
{
if(bt.available()>0){
val=bt.read();
Serial.println(val);
digitalWrite(led,val);
}
}


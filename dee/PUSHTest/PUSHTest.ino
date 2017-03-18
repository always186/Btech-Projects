int d=2;
void setup()
{
  Serial.begin(9600);
  pinMode(14,INPUT);
pinMode(13,OUTPUT);

}
void loop()
{
d=digitalRead(2);
Serial.println(d);
if(d==0)
{digitalWrite(13,HIGH);}
else
{digitalWrite(13,LOW);}
delay(1000);
}

const int led=13;
int val=0;
void setup()
{
Serial.begin(38400);
pinMode(led,OUTPUT);
}
void loop()
{
if(Serial.available()>0){
val=Serial.read();
digitalWrite(led,val);
}
}


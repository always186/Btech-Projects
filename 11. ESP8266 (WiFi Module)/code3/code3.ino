void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
Serial2.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial2.available()>0)
{
  byte b=Serial2.read();
  Serial.write(b);
}
if(Serial.available()>0)
{
  byte c=Serial.read();
Serial2.write(c);
}}

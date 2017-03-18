const int button=8;
int val=0;
void setup()
{
Serial.begin(38400);
pinMode(button,INPUT);
}
void loop()
{
val=digitalRead(button);
Serial.write(char(val));
}


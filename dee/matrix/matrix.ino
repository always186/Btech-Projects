int ledPins[] = {2,3,4,5,6,7,8,9}; //An array to hold the pin each LED is connected to
void setup()
{
 
  for(int i = 0; i < 8; i++){         //this is a loop and will repeat eight times
      pinMode(ledPins[i],OUTPUT); //we use this to set each LED pin to output
  }
}
void loop()
{
  for(int i=0;i<=7;i++)
  {
    int offLed=i-1;
    if(i==0)
    {
      offLed=7;
    }
    digitalWrite(ledPins[i],HIGH);
    digitalWrite(ledPins[offLed],LOW);
    delay(1000);
  }
}


/*
Arduino Tutorials
Episode 2
Switch3 Program (debounced)
Written by: Jeremy Blum
*/

int switchPin = 14;
int ledPin = 13;
boolean lastButton = LOW;
boolean currentButton = LOW;
boolean ledOn = false;

void setup()
{
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
}


void loop()
{
  Serial.println(digitalRead(switchPin));
  delay(500);
}

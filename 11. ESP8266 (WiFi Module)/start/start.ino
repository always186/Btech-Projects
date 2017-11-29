void setup()
{
  Serial.begin(115200);
  Serial.print("AT+RST\r\n");
}
 
void loop()
{
 while(Serial.available())
      {
        Serial.print(Serial.read()); 
    }
}

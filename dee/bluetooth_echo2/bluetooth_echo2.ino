#include <SoftwareSerial.h>
//D10   >>>  Rx
// D11   >>>  Tx
String message; //string that stores the incoming message
SoftwareSerial mySerial(10, 11);

void setup()
{
  Serial.begin(115200); 
  mySerial.begin(9600);
  //set baud rate
}

void loop()
{
  while(mySerial.available())
  {//while there is data available on the serial monitor
    message+=char(mySerial.read());//store string from serial command
  }
  
  if(!mySerial.available())
  {
    if(message!="")
    {//if data is available
      Serial.println(message); //show the data
      message=""; //clear the data
    }
    
  }
  
  delay(3000); //delay
}
    

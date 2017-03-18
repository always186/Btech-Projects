#include <SoftwareSerial.h>// import the serial library
//#include "Keyboard.h"
#include "HID.h"
SoftwareSerial BT(10, 11); // RX, TX
int ledpin=3; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  BT.begin(9600);
  Serial.begin(9600);
    Serial.println("INtiating");
  BT.println("Initiating");
 

}

void loop() {


if(Serial.available())
{
  BT.print(Serial.readString());
  Serial.println(String(Serial.readString()));
  
  }

else if(BT.available())
{
  Serial.println(String(BT.readString()));
    BT.println(BT.readString());

  }
  

}

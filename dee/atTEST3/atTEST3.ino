#include <SoftwareSerial.h>

SoftwareSerial BT(10, 11); // RX, TX

int KEY_PIN = 4; // set mode of the Bluetooth (AT or Pairing mode)

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(38400); // for AT mode
  /*while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }*/

  // set the data rate for HC-05
  BT.begin(38400);

  pinMode(KEY_PIN, OUTPUT);
  
  digitalWrite(KEY_PIN, HIGH); // AT mode
  //digitalWrite(KEY_PIN, LOW); // Pairing mode
  
  delay(500);
}

void loop() 
{
  if (BT.available())
    Serial.write(BT.read()); // write all on the SerialMonitor what is getting from Bluetooth
  if (Serial.available()>0)
    BT.write(Serial.read()); // write to Bluetooth all is getting from SerialMonitor
}


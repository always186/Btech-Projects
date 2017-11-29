#include "ThingSpeak.h"
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {  0x98, 0x4F, 0xEE, 0x05, 0x38, 0x01 };
EthernetClient client;
unsigned long myChannelNumber = 31461;
const char * myWriteAPIKey = "LD79EOAAWRVYF04Y";
void setup() {
Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for(;;)
      ;
  }  
   system("ifup eth0");
  ThingSpeak.begin(client);
}
void loop() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
  ThingSpeak.writeField(myChannelNumber, 1, voltage, myWriteAPIKey);
  delay(20000); // ThingSpeak will only accept updates every 15 seconds.
}

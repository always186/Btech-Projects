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
  float pinVoltage = analogRead(A0) * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
  ThingSpeak.setField(1,pinVoltage);
    pinVoltage = analogRead(A1) * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
    ThingSpeak.setField(2,pinVoltage);
    pinVoltage = analogRead(A2) * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
    ThingSpeak.setField(3,pinVoltage);
    pinVoltage = analogRead(A3) * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
    ThingSpeak.setField(4,pinVoltage);
    pinVoltage = analogRead(A4) * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
    ThingSpeak.setField(5,pinVoltage);
    pinVoltage = analogRead(A5) * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
    ThingSpeak.setField(6,pinVoltage);
    pinVoltage = analogRead(A6) * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
    ThingSpeak.setField(7,pinVoltage);
    pinVoltage = analogRead(A7) * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
    ThingSpeak.setField(8,pinVoltage);
  // Write the fields that you've set all at once.
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  

  delay(20000); // ThingSpeak will only accept updates every 15 seconds. 
}

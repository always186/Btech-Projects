#include "ThingSpeak.h"
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {  0x98, 0x4F, 0xEE, 0x05, 0x38, 0x01 };
EthernetClient client;
unsigned long channel = 12397;
unsigned int field = 4;
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
  // Read the latest value from field 4 of channel 12397
  float temperatureInF = ThingSpeak.readFloatField(channel, field);
  Serial.print("Current temp is: "); 
  Serial.print(temperatureInF);
  Serial.println(" degrees F"); 
  delay(30000); // Note that the weather station only updates once a minute
}






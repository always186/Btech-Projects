#include "ThingSpeak.h"
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {  0x98, 0x4F, 0xEE, 0x05, 0x38, 0x01 };
EthernetClient client;
unsigned long myChannelNumber = 31461;
const char * myReadAPIKey = "NKX4Z5JGO4M5I18A";
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
  // Read the latest value from field 1 of channel 31461
  float voltage = ThingSpeak.readFloatField(myChannelNumber, 1, myReadAPIKey);  
  Serial.print("Latest voltage is: "); 
  Serial.print(voltage);
  Serial.println("V"); 
  delay(30000);
}

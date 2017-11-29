#include <ThingSpeak.h>
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {  0x98, 0x4F, 0xEE, 0x05, 0x38, 0x01 };
EthernetClient client;
unsigned long channel = 1417;
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
  String color = ThingSpeak.readStringField(channel, 1);//here 1 indicates the coloumn number
  Serial.println(color);
  delay(5000);
}

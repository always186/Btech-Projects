#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {  0x98, 0x4F, 0xEE, 0x05, 0x38, 0x01 };
//initiallising as client
EthernetClient client;
void setup() {
Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for(;;)
      ;
  }
  Serial.println("connecting...");
  //system("ifconfig");
  Serial.println(system("ifconfig"));
  /*system("ifup eth0");
  Serial.println("connecting...");
  IPAddress my=Ethernet.localIP();
  Serial.println(my);*/
}

void loop()
{
 }

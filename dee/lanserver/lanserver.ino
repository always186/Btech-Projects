#include <SPI.h>
#include <Ethernet.h>
// MAC address for the Galileo (there’s a  on the Ethernet connector)
byte mac[] = { 0x98, 0x4F, 0xEE, 0x05, 0x3E, 0x07 };
//the IP address for the Galileo: (will be used if there’s no DHCP server on your network)
byte ip[] = { 192, 168, 1, 15 };
void setup() {
  Serial.begin(9600);
delay(5000);
Serial.println("Attempting to configure Ethernet using DHCP");
if (Ethernet.begin(mac) == 0) {

Serial.println("Failed to configure Ethernet using DHCP");
Serial.println("Attempting to configure Ethernet using Static IP");
Ethernet.begin(mac, ip);
Serial.println(" Please check ifconfig");
} else
Serial.println("Sounds good");
system("ifup eth0"); // load Ethernet interface!
}
void loop () {}


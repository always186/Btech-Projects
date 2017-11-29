#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {  0x98, 0x4F, 0xEE, 0x05, 0x38, 0x01 };
char server[] = "api.thingspeak.com";
EthernetClient client;
int i=67;
//to update the channel feed: GET https://api.thingspeak.com/update?api_key=SHY8LCD01A1M2D5Y&field1=0
void setup() {
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for(;;)
      ;
  }  
    system("ifup eth0");
    for(int i=89;i<150;i++){
  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.print("GET /update?api_key=SHY8LCD01A1M2D5Y&field1=");
    client.println(i);
    client.println();
    while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  client.stop();
  } 
  else {
    Serial.println("connection failed");
  }
  delay(15000);
}}


void loop()
{
}


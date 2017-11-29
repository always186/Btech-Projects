#include "ThingSpeak.h"
#include <SPI.h>
#include <Ethernet.h>
byte mac[] = {  0x98, 0x4F, 0xEE, 0x05, 0x38, 0x01 };
EthernetClient client;
/*
  This is the ThingSpeak channel number for the MathwWorks weather station
  https://thingspeak.com/channels/12397.  It senses a number of things and puts them in the eight
  field of the channel:
  Field 1 - Wind Direction (degrees where 0 is North)
  Field 2 - Wind Speed (MPH)
  Field 3 - Humidity (%RH)
  Field 4 - Temperature (Degrees F)
  Field 5 - Rainfall (inches since last measurement)
  Field 6 - Atmospheric Pressure (inHg)
*/
unsigned long weatherStationChannelNumber = 12397;

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
  float windDirection = ThingSpeak.readFloatField(weatherStationChannelNumber,1);
  float windSpeed = ThingSpeak.readFloatField(weatherStationChannelNumber,2);
  float humidity = ThingSpeak.readFloatField(weatherStationChannelNumber,3);
  float temperature = ThingSpeak.readFloatField(weatherStationChannelNumber,4);
  float rainfall = ThingSpeak.readFloatField(weatherStationChannelNumber,5);
  float pressure = ThingSpeak.readFloatField(weatherStationChannelNumber,6);

  Serial.println("======================================"); 
  Serial.println("Current weather conditions in Natick: "); 
  Serial.print(temperature);
  Serial.print(" degrees F, "); 
  Serial.print(humidity);
  Serial.println("% humidity"); 
  Serial.print("Wind at ");
  Serial.print(windSpeed);
  Serial.print(" MPH at "); 
  Serial.print(windDirection);
  Serial.println(" degrees"); 
  Serial.print("Pressure is ");
  Serial.print(pressure);
  Serial.print(" inHg");
  if(rainfall > 0)
  {
  	Serial.print(", and it's raining"); 
  }
  Serial.println(); 
  delay(60000); // Note that the weather station only updates once a minute
}

//D5  >>>  Rx
// D6   >>>  Tx
#include <SoftwareSerial.h>// import the serial library

SoftwareSerial Genotronex(10, 11); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
int BluetoothData; // the data given from Computer

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Genotronex.begin(9600);
  Genotronex.println("Bluetooth On please press 1 or 0 blink LED ..");
  pinMode(ledpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Genotronex.available()){
BluetoothData=(Genotronex.read()).toInt();
Serial.println(BluetoothData);
  delay(1000); 
}
delay(100);// prepare for next data ...
}

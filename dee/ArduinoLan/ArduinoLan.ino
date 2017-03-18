/*
  This Sketch configures Ethernet Networking in the Galileo Board and 
  turns on an LED on for 200 ms , then off for 200 ms, repeatedly.

  This example code is in the public domain.
 */

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

// the setup routine runs once when you press reset:
void setup() {  
  // Activate Telnet
  system("telnetd -l /bin/sh");

  //169.254.1.1 is the IP Address we are giving here to the Galileo board
  system("ifconfig eth0 192.168.1.15 netmask 255.255.255.0 up"); 

  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  //THIS IS SUPPOSED TO BE "OK" IN MORSE  _ _ _ _._  
  //http://morsecode.scphillips.com/jtranslator.html
  digitalWrite(led, HIGH);   
  delay(400);               
  digitalWrite(led, LOW);    
  delay(100);   
  digitalWrite(led, HIGH);   
  delay(400);               
  digitalWrite(led, LOW);    
  delay(100); 
  digitalWrite(led, HIGH);   
  delay(400);               
  digitalWrite(led, LOW);    
  delay(400); 

  digitalWrite(led, HIGH);   
  delay(400);               
  digitalWrite(led, LOW);    
  delay(100);   
  digitalWrite(led, HIGH);   
  delay(200);               
  digitalWrite(led, LOW);    
  delay(100); 
  digitalWrite(led, HIGH);   
  delay(400);               
  digitalWrite(led, LOW);    
  delay(1000);   
}

#include <SoftwareSerial.h>// import the serial library
char val; // variable to receive data from the serial port
//int ledpin = 13;

SoftwareSerial BTSerial(0,1);

void setup() {
  //pinMode(7, OUTPUT); //motor 1 pins
    //pinMode(6, OUTPUT); //motor 2 pin 
  Serial.begin(9600);       
  BTSerial.begin(9600);   
      //digitalWrite(7,LOW);
  //digitalWrite(6,LOW);
}

void loop() {
  
  if( BTSerial.available())       // if data is available to read
  {
   if(BTSerial.read()!=0)
 {   
  Serial.println(BTSerial.read());
  if(BTSerial.read()<9)
  {
   /* digitalWrite(6,HIGH);
  digitalWrite(7,LOW);*/
  Serial.println("LEFT");
     /* delay(100);    

  digitalWrite(7,LOW);
  digitalWrite(6,LOW);*/
    //delay(1);   
   
// wait 100ms for next reading

  }

  else if((BTSerial.read())>=9 && (BTSerial.read())<11)
  {
    /*digitalWrite(7,HIGH);
  digitalWrite(6,HIGH);*/
    Serial.println("FORWARD");
    /*delay(100);                   
    digitalWrite(7,LOW);
  digitalWrite(6,LOW);
//      delay(1); */   

  }

   else if((BTSerial.read())>=11 && (BTSerial.read())<20)
  {
    //digitalWrite(7,HIGH); 
  //digitalWrite(6,LOW);
      Serial.println("RIGHT");

   /* delay(100);                    // wait 100ms for next reading
    digitalWrite(7,LOW);
  digitalWrite(6,LOW);*/
    //  delay(1);    

  }}
  
} // delay(20);                    
}

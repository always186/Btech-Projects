/*
*  GSM Holiday Star
*  Use SMS and Arduino GSM shield to control
*  LED patterns on a Holiday Star
*
*  You need Intel Galileo, Arduino GSM shield,
*  7 short stirps of white LED strip and 1
*  long strip of blue LED strip. 
*
*  (c) 2013 Arduino Verkstad
*
*/
#include <GSM.h>
#define PINNUMBER ""

//Number of pins for white led strips
#define NUMPINS 7

//Pins used for white led strips
int pins[]={13,12,11,10,8,6,5};
//Pin used for the led ring
int ringPin=9;

GSM gsmAccess;
GSM_SMS sms;

//Status of the sms command
int currentMode=0;
char msg[200];

void setup() {
  Serial.begin(9600);
  
  // Initialize the pins for white led strips
  for(int i=0;i<NUMPINS;i++){
    pinMode(pins[i],OUTPUT);
  }
  
  //Random seed for random patten
  randomSeed(analogRead(0));
  
  //Initialize GSM shield
  initSMS();
}

void loop() {
  //First make sure all led strips are dimmed
  clearAll();
  
  //Depending on current mode, display different patterns
  switch(currentMode){
    case 0:
      turnOff();
      break;
    case 1:
      peacockPatten();
      break;
    case 2:
      clockPatten();
      break;
    case 3:
      randomPatten();
      break;
  }
}



/*
*
*  Different pattens, and LED control
*
*/
void turnOff(){
  //Get sms command, quit to main loop if receiving command
  if(procSMS())return;

}

void peacockPatten(){
  for(int i=0;i<NUMPINS/2+1;i++){
    digitalWrite(pins[i],HIGH);
    digitalWrite(pins[NUMPINS-i-1],HIGH);
    delay(200);
    
    //Get sms command, quit to main loop if receiving command
    if(procSMS())return;

  }
  //Display a breath patten for the middle ring
  ringBreath();

  for(int i=0;i<NUMPINS/2+1;i++){
    digitalWrite(pins[i],LOW);
    digitalWrite(pins[NUMPINS-i-1],LOW);
    delay(200);
    
    //Get sms command, quit to main loop if receiving command
    if(procSMS())return;

  }
}

void clockPatten(){
  for(int i=0;i<NUMPINS;i++){
    digitalWrite(pins[i],HIGH);
    digitalWrite(pins[(i+NUMPINS-1)%NUMPINS],LOW);
    delay(400);
    
    //Get sms command, quit to main loop if receiving command
    if(procSMS())return;

  }
  digitalWrite(pins[NUMPINS-1],LOW);
  
  //Display a breath patten for the middle ring
  ringBreath();
}

void randomPatten(){
  int pin=random(NUMPINS);
  digitalWrite(pins[pin],HIGH);
  delay(30);
  digitalWrite(pins[pin],LOW);
  
  //Get sms command, quit to main loop if receiving command
  if(procSMS())return;
}

void ringBreath(){
  for(int i=0;i<510;i+=10){
    analogWrite(ringPin,255-abs(i-255));
    delay(30);
  }
  analogWrite(ringPin,0);
}

void clearAll(){
  for(int i=0;i<NUMPINS;i++){
    digitalWrite(pins[i],LOW);
  }
  analogWrite(ringPin,0);
}



/*
*
*  SMS related mechanisms
*
*/

//Initializing the GSM shield
void initSMS(){
  // connection state
  boolean notConnected = true;

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected){
    if(gsmAccess.begin(PINNUMBER)==GSM_READY){
      notConnected = false;
    }
    else{
      Serial.println("Not connected");
      delay(1000);
    }
  }
  
  Serial.println("GSM initialized");
}

//Reads SMS, get the current mode and returns the status
boolean procSMS(){
  //If receives a SMS, return true
  if(getSMS()){
    //Here we specify the commands. Make sure you send the exact same
    if(compareSMS(msg,"cmd 1")){
      currentMode=1;
    }else if(compareSMS(msg,"cmd 2")){
      currentMode=2;
    }else if(compareSMS(msg,"cmd 3")){
      currentMode=3;
    }else if(compareSMS(msg,"stop")){
      currentMode=0;
    }
    return true;
  }
  return false;
}

//This function gets sms message from the gSM shield and stores it
boolean getSMS(){
  char c;
  int msgPos=0;
  
  if (sms.available()){
    if(sms.peek()=='#'){
      Serial.println("Discarded SMS");
      sms.flush();
    }
    
    while(c=sms.read()){
      msg[msgPos]=c;
      msgPos++;
    }
    //Add a \0 to the end of the message, to indicate it is finished
    msg[msgPos]='\0';
    Serial.println(msg);
    
    sms.flush();

    return true;
  }
  return false;
}



/*
*
*  Utility
*
*/
boolean compareSMS(char* toComp, char* orig){
  String orig2=String(orig);
  return orig2==toComp;
}


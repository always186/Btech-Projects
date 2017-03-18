#include <GSM.h>

#define PINNUMBER "1234"
# define led 13
// initialize the library instance
GSM gsmAccess(true);
GSM_SMS sms;

int threshold=75;
int sensorsound=9;
int sensortouch=5;
float sound;
int touch;
int count=0;

void setup() {

 // Serial1.begin(9600); 
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  pinMode(sensorsound,INPUT);
   pinMode(sensortouch,INPUT);
    Serial.println("SMS Messages Sender");

  // connection state
  boolean notConnected = true;
 
  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while(notConnected)
  {
    if(gsmAccess.begin(PINNUMBER)==GSM_READY)
      notConnected = false;
    else
    {
      Serial.println("Not connected");
      delay(1000);
    }
  }
  
  Serial.println("GSM initialized");
   
   
}

void loop()
{
  
 sound= analogRead(sensorsound);
 touch= digitalRead(sensortouch);
 if(touch==HIGH)
 {
   count = count+1;
   touch = digitalRead(sensortouch);
   if(touch==HIGH)
   count = count+1;
 }
 
 if((count>=2)||(sound>threshold))
 {
   digitalWrite(led,HIGH);
 sendMessage();
 
 }
}

void sendMessage()
{
  Serial.print("Enter a mobile number: ");
  char remoteNum[20]="9818551449";  // telephone number to send sms
  //readSerial(remoteNum);
  Serial.println(remoteNum);
    
  // sms text
 /* Serial.print("Now, enter SMS content: ");
  char txtMsg[200];
  readSerial(txtMsg);*/
  Serial.println("SENDING");
  Serial.println();
  Serial.println("Message:");
  String txtMsg = "I am in trouble";
  Serial.println(txtMsg);
  
  // send the message
  sms.beginSMS(remoteNum);
  sms.print(txtMsg);
  sms.endSMS(); 
  Serial.println("\nCOMPLETE!\n");

}
int readSerial(char result[])
{
  int i = 0;
  while(1)
  {
    while (Serial.available() > 0)
    {
      char inChar = Serial.read();
      if (inChar == '\n')
      {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if(inChar!='\r')
      {
        result[i] = inChar;
        i++;
      }
    }
  }
}



 


#define led1 9
#define led2 6
#define led3 7
#define led4 8
String text;
#include <GSM.h>

#define PINNUMBER ""

// initialize the library instance
GSM gsmAccess(true);
GSM_SMS sms;

void setup() {
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  Serial.begin(9600);
 Serial2.begin(9600);
  
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
  if(Serial1.available()>0)
  { text=Serial2.readString();
    Serial.println(text);
    if(text==" roomoneon")
    { digitalWrite(led1,HIGH);
    Serial.print("Enter a mobile number: ");
  char remoteNum[20]="9818090091";  // telephone number to send sms
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
    else if(text=="roomoneoff")
    { digitalWrite(led1,LOW);
    } 
    else if(text=="roomtwoon")
    { digitalWrite(led2,HIGH);
    } 
    else if(text=="roomtwooff")
    { digitalWrite(led2,LOW);
    } 
    else if(text=="roomthreeon")
    { digitalWrite(led3,HIGH);
    } 
    else if(text=="roomthreeoff")
    { digitalWrite(led3,LOW);
    }
    else if(text=="roomfouron")
    { digitalWrite(led4,HIGH);
    } 
    else if(text=="roomfouroff")
    { digitalWrite(led4,LOW);
    } 
    else
    { digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      digitalWrite(led4,LOW);
    }
     
  }

  delay(500);   
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


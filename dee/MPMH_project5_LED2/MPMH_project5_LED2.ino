#define lock 8
#define unlock 9
const int analogInPin = A0;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;
String readString;
String UserID[]={"","","","","","","",""};
String PoleID[]={"","","","","","","",""};
String Area[]={"","","","","","","",""};
String state[]={"","","","","","","",""};
int i=0; 
#define DEBUG true
//Serial1(19,18); RX TX
//Serial2(17,16); RX TX

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200); // your esp's baud rate might be different
  Serial2.begin(9600);
  Serial3.begin(9600);
  pinMode(lock,OUTPUT);
  pinMode(unlock,OUTPUT);
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
  
}
 
void loop()
{
  while(true)
  {
    sensorValue = analogRead(analogInPin);
    outputValue = map(sensorValue, 0, 1023, 0, 255);
     if (sensorValue>280&& outputValue>50)
  {
   Serial.println(sensorValue);   
  Serial.println("WELCOME!!");
  break;
  }
  }
  while (Serial2.available()) {
    delay(3);  
    char c = Serial2.read();
    readString += c; 
  }
  if (readString.length() >0) {
    Serial.println(readString);
    if (readString != "")  //second generated string from android
  {
  digitalWrite(5,HIGH); 
  delay(300); 
  String stringOne = readString;
  Serial3.println(stringOne);
  state[i] = stringOne.substring(0,1);
  if(state[i]=="1")
  {
    state[i]="LOCKED";
    digitalWrite(lock,HIGH);
    digitalWrite(unlock,LOW);
    
  }
  else
  {
    state[i]="UNLOCKED";
    digitalWrite(lock,LOW);
    digitalWrite(unlock,HIGH);
  }
  UserID[i]=stringOne.substring(1,6);
  PoleID[i]=stringOne.substring(5,6);
  Area [i] =stringOne.substring(6,11);
  if(Area[i]=="dwrka")
  Area[i]="Dwarka";
  else if(Area[i]=="lodrd")
  Area[i]="Lodhi Road";
   else if(Area[i]=="munki")
  Area[i]="Munirka";
   else if(Area[i]=="kasga")
  Area[i]="Kashmere Gate";
  else if(Area[i]=="noida")
  Area[i]="Noida";
  Serial.println(UserID[i]);
  Serial.println("yeyy");
  i++;
  readString="";
    }
  else
   {
    digitalWrite(5,LOW); 
   }
 }
  if(Serial1.available()) // check if the esp is sending a message 
  {
    
    if(Serial1.find("+IPD,"))
    {
     delay(1000);
 
     int connectionId = Serial1.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
     
     String webpage =  "<html><head><style>table, th, td {  border: 1px solid black; }}th, td {padding: 40px;</style><TITLE>CYCLOCK</TITLE></head><body><H1> WELCOME TO CYCLOCK</H1><br><br><br><table style=width:100%><tr><td>POLE NUMBER</td><td>AREA</td><td>CYCLE ID</td><td>STATE</td></tr>";
 
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     
     webpage="<tr><td>"+PoleID[0]+"</td><td>"+Area[0]+"</td><td>"+UserID[0]+"</td><td>"+state[0]+"</td></tr>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     webpage="<tr><td>"+PoleID[1]+"</td><td>"+Area[1]+"</td><td>"+UserID[1]+"</td><td>"+state[1]+"</td></tr>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     webpage="<tr><td>"+PoleID[2]+"</td><td>"+Area[2]+"</td><td>"+UserID[2]+"</td><td>"+state[2]+"</td></tr>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     
     webpage="<tr><td>"+PoleID[3]+"</td><td>"+Area[3]+"</td><td>"+UserID[3]+"</td><td>"+state[3]+"</td></tr>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     webpage="<tr><td>"+PoleID[4]+"</td><td>"+Area[4]+"</td><td>"+UserID[4]+"</td><td>"+state[4]+"</td></tr>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     webpage="<tr><td>"+PoleID[5]+"</td><td>"+Area[5]+"</td><td>"+UserID[5]+"</td><td>"+state[5]+"</td></tr>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     webpage="</table></body></html>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
 
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,3000,DEBUG);
    }
  }
}
 
 
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    Serial1.print(command); // send the read character to the Serial1
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(Serial1.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = Serial1.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

#include <SoftwareSerial.h>
 String UserID2="";
 String PoleID2="";
 String Area2="";
#define DEBUG true
String readString; 
SoftwareSerial esp8266(10,11); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 23, 9, 8, 3, 2);//23 on place of 11
void setup()
{
  Serial.begin(9600);
  esp8266.begin(115200); // your esp's baud rate might be different
  lcd.begin(16, 2);
  pinMode(5,OUTPUT);
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}
 
void loop()
{ 
  String stringOne = "";
  digitalWrite(5,LOW); 
  //Bluetooth Block
  while (Serial.available()) {
    delay(3);  
    char c = Serial.read();
    readString += c; 
  }
  if (readString.length() >0) {
   stringOne = readString;
    Serial.println(stringOne);
    
    if (readString != "")  //second generated string from android
    {
      digitalWrite(5,HIGH); 
     //Serial.write("156dedwrka123");
      delay(300); 
      Serial.println("yeyy");//Wait 3 sec
      //digitalWrite(relay, LOW);
    readString="";
  }
  else
  {
    digitalWrite(5,LOW); 
  }
 }
 //bluetooth finish
 //LCD

if(stringOne!="")
{lcd.setCursor(0, 0);
   
   
//  String stringOne="AashviPriyanshiHarleenDeeskha";
  
  String state = stringOne.substring(0,1);
  if(state=="1")
  {
    state="LOCKED";
    
  }
  else
  {
    state="UNLOCKED";
  }
  String UserID=stringOne.substring(1,6);
  String PoleID=stringOne.substring(5,6);
  String Area=stringOne.substring(6,11);
  
  if(Area=="dwrka")
  Area="Dwarka";
  else if(Area=="lodrd")
  Area="Lodhi Road";
   else if(Area=="munki")
  Area="Munirka";
   else if(Area=="kasga")
  Area="Kashmere Gate";
  else if(Area=="noida")
  Area="Noida";
  String Cycle_No=stringOne.substring(11,14);
  if(Area !="")
  Area2=Area;
  if(UserID !="")
  UserID2=UserID;
  if(PoleID != "")
  PoleID2=PoleID;
 // Serial.println(UserID);
  lcd.print(UserID);
  delay(40);
  lcd.setCursor(0,1);
  lcd.print(Area);
  delay(4);
  lcd.setCursor(6,1);
  lcd.print(Cycle_No);
  delay(4);
}
  if(esp8266.available()) // check if the esp is sending a message 
  {
    
    
    if(esp8266.find("+IPD,"))
    {
     delay(1000);
 
     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
                                          
                                           //HARLEEN IS ADDING FROM HERE:the webpage code
     
     String webpage = "<html><head><style>table, th, td {  border: 1px solid black; }}th, td {padding: 40px;</style><TITLE>CYCLOCK</TITLE></head><body><H1> WELCOME TO CYCLOCK</H1><br><br><br><table style=width:100%><tr><td>POLE NUMBER</td><td>AREA</td><td>CYCLE ID</td></tr><tr><td>"+PoleID2+"</td><td>"+Area2+"</td><td>"+UserID2+"</td></tr></table></body></html>";
 
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);

                                                                        
                                                                        



     
   /*  webpage="<button>LED2</button>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);*/ //COMMENTED BY HARLEEN 
 
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
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
       
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
        
      }  
    }
    
    if(debug)
    {
      Serial.println(response);
    }
    
    return response;
}

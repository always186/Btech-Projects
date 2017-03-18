int var=0;
#include <Servo.h>

#include <SoftwareSerial.h>
String UserID[10]={"","","","","","","","","",""};
String PoleID[10]={"","","","","","","","","",""};
String Area[10]={"","","","","","","","","",""};
String Cycle_No[10]={"","","","","","","","","",""};    
 
int push1 = 33; 
  int push2=35;
  int val1=0;
  int val2=0;
  int n=0;
 String UserID2="";
 String PoleID2="";
 String Area2="";
 int i=1;
#define DEBUG true
Servo myservo1;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
Servo myservo2;
 
int pos = 0;  
String readString; 
SoftwareSerial esp8266(10,11); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 22, 9, 8, 3, 2);//22 on place of 11
void setup()
{
  Serial.begin(9600);
  esp8266.begin(115200); // your esp's baud rate might be different
  lcd.begin(16, 2);
  pinMode(5,OUTPUT);
 pinMode(push1,INPUT);     //pushbutton 1
  pinMode(push2,INPUT);
   pinMode(32 ,OUTPUT);   
  pinMode(34 ,OUTPUT);
  digitalWrite(32,HIGH);
 digitalWrite(34,HIGH);
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
  myservo1.attach(6);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(7);
  
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
  val1=digitalRead(push1);
  val2=digitalRead(push2);
  if(val1==HIGH)
  {
  PoleID[0]="1pole1";
  
  }
  else  if(val2==HIGH)
  {
  PoleID[0]="1pole2";
  } 
  else
 PoleID[0]="nnone";
  
  if(state=="1"&&(PoleID[0]=="1pole1"||PoleID[0]=="1pole2"))
  {
    state="LOCKED";
    for(pos =120; pos>=1; pos-=1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo1.write(pos);              // tell servo to go to position in variable 'pos' 
    myservo2.write(pos);
    delay(3);                       // waits 15ms for the servo to reach the position 
   } 
    
   n==0;
       

  }
  else if(state=="0"&&(PoleID[0]=="1pole1"||PoleID[0]=="1pole2"))
  {
    state="UNLOCKED";
    for(pos = 0; pos < 120; pos += 1)     // goes from 180 degrees to 0 degrees //pos =120; pos>=1; pos-=1
  {                                
    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
    myservo2.write(pos);
    delay(3);                       // waits 15ms for the servo to reach the position 
   
  } 
  /*val1=digitalRead(push1);
   val2=digitalRead(push2);
   
   if(push1==HIGH)
      PoleID[0]="0pole1";
   else  if(push2==HIGH)
       PoleID[0]="0pole2"; 
       else
       PoleID[0]="none";*/
       n==0;
  }
  UserID[0]=stringOne.substring(1,6);
  //PoleID[0]=stringOne.substring(5,6);
  Area[0]=stringOne.substring(6,11);
 
  if(Area[0]=="dwrka")
  Area[0]="Dwarka";
  else if(Area[0]=="lodrd")
  Area[0]="Lodhi Road";
   else if(Area[0]=="munki")
  Area[0]="Munirka";
   else if(Area[0]=="kasga")
  Area[0]="Kashmere Gate";
  else if(Area[0]=="noida")
  Area[0]="Noida";
  Cycle_No[0]=stringOne.substring(11,14);
  if(Area[0] !="")
  Area[i]=Area[0];
  if(Cycle_No[0] !="")
  Cycle_No[i]=Cycle_No[0];
  if(PoleID[0] != "")
  PoleID[i]=PoleID[0].substring(1,6);
 // Serial.println( Cycle_No);
  lcd.print(UserID[0]);
  delay(40);
  lcd.setCursor(0,1);
  lcd.print(Area[0]);
  delay(4);
  lcd.setCursor(9,1);
  lcd.print(Cycle_No[0]);
  delay(4);
  lcd.setCursor(9,0);
  lcd.print(state);
  delay(4);
  i++;
}
  if(esp8266.available()) // check if the esp is sending a message 
  {
    
    
    if(esp8266.find("+IPD,"))
    {
     delay(1000);
 
     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
                                          
                                           //HARLEEN IS ADDING FROM HERE:the webpage code
     
     String webpage = "<html><head><style>table, th, td {  border: 1px solid black; }}th, td {padding: 40px;</style><TITLE>CYCLOCK</TITLE></head><body><H1> WELCOME TO CYCLOCK</H1><br><br><br><table style=width:100%><tr><td>POLE NUMBER</td><td>AREA</td><td>CYCLE ID</td></tr><tr><td>"+PoleID[1]+"</td><td>"+Area[1]+"</td><td>"+ Cycle_No[1]+"</td></tr>";
 
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
  
  webpage="<tr><td>"+PoleID[2]+"</td><td>"+Area[2]+"</td><td>"+ Cycle_No[2]+"</td></tr>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);//COMMENTED BY HARLEEN 
                                                                        
                                                                        



     
   webpage=" <tr><td>"+PoleID[3]+"</td><td>"+Area[3]+"</td><td>"+ Cycle_No[3]+"</td></tr>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);//COMMENTED BY HARLEEN 
     webpage="<tr><td>"+PoleID[4]+"</td><td>"+Area[4]+"</td><td>"+ Cycle_No[4]+"</td></tr></table></body></html>";
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);//COMMENTED BY HARLEEN 
 
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

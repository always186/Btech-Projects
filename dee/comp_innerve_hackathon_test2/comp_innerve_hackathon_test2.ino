#include <SPI.h>
#include <Ethernet.h>

#include <Servo.h> 
 
Servo myservo;
#include <SD.h>
#define led1 9
#define led2 6
#define led3 7
#define led4 8
// size of buffer used to capture HTTP requests
#define REQ_BUF_SZ   20
String text;

  // analog pin used to connect the potentiometer
int val; 

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0x98, 0x4F, 0xEE, 0x05, 0x3E, 0xC9 };
IPAddress ip(172, 16, 11, 88); // IP address, may need to change depending on network
EthernetServer server(80);  // create a server at port 80
File webFile;
char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
char req_index = 0;              // index into HTTP_req buffer
int pos=0; 

void setup()
{
  myservo.attach(11);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);   // disable Ethernet chip
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
      Serial1.begin(9600);

    //pinMode(11,OUTPUT);
    Serial.begin(9600);       // for debugging
    
    // initialize SD card
    Serial.println("Initializing SD card...");
    if (!SD.begin(4)) {
        Serial.println("ERROR - SD card initialization failed!");
        return;    // init failed
    }
    Serial.println("SUCCESS - SD card initialized.");
    // check for index.htm file
    if (!SD.exists("led.htm")) {
        Serial.println("ERROR - Can't find led.htm file!");
        return;  // can't find index file
    }
    Serial.println("SUCCESS - Found led.htm file.");
    
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
}

void loop()
{
if(Serial1.available()>0)
  { text=Serial1.readString();
    Serial.println(text);
    if(text==" roomoneon")
    { digitalWrite(led1,HIGH);
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




  //----------------------------------------------------------------------
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                // buffer first part of HTTP request in HTTP_req array (string)
                // leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
                if (req_index < (REQ_BUF_SZ - 1)) {
                    HTTP_req[req_index] = c;          // save HTTP request character
                    req_index++;
                }
                // print HTTP request character to serial monitor
                Serial.print(c);
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // open requested web page file
                    if (StrContains(HTTP_req, "GET / ")
                                 || StrContains(HTTP_req, "GET /index.htm")) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: text/html");
                        client.println("Connnection: close");
                        client.println();
                        webFile = SD.open("login.html");        // open web page file
                    }

               else if(StrContains(HTTP_req, "GET /target.html"))
                {webFile = SD.open("target.html");}

            else if(StrContains(HTTP_req, "GET /on.html"))
                {//digitalWrite(11,HIGH);
            
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
                  
                  webFile = SD.open("target.html");}
                    
   else if(StrContains(HTTP_req, "GET /off.html"))
                {//digitalWrite(11,LOW);
            
  for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
                  webFile = SD.open("target.html");}
                    
                    if (webFile) {
                        while(webFile.available()) {
                            client.write(webFile.read()); // send web page to client
                        }
                        webFile.close();
                    }
                    // reset buffer index and all buffer elements to 0
                    req_index = 0;
                    StrClear(HTTP_req, REQ_BUF_SZ);
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)



}

// sets every element of str to 0 (clears array)
void StrClear(char *str, char length)
{
    for (int i = 0; i < length; i++) {
        str[i] = 0;
    }
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char StrContains(char *str, char *sfind)
{
    char found = 0;
    char index = 0;
    char len;

    len = strlen(str);
    
    if (strlen(sfind) > len) {
        return 0;
    }
    while (index < len) {
        if (str[index] == sfind[found]) {
            found++;
            if (strlen(sfind) == found) {
                return 1;
            }
        }
        else {
            found = 0;
        }
        index++;
    }

    return 0;
}


String readString;
String UserID[]={"","","","","","","",""};
String PoleID[]={"","","","","","","",""};
String Area[]={"","","","","","","",""};
int i=0;
int val=0;
void setup() {
  Serial2.begin(9600);
  Serial.begin(115200);
  Serial3.begin(9600);
}

void loop() {
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
  String state = stringOne.substring(0,1);
  if(state=="1")
  {
    state="LOCKED";
  }
  else
  {
    state="UNLOCKED";
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
  Serial.println("UserID"+UserID[i]+"Area"+Area[i]);
  Serial.println("yeyy");
  i++;
  readString="";
    }
  else
   {
    digitalWrite(5,LOW); 
   }
 }
 
}

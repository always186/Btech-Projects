#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
#define remote A0
#define sensor1 A1
#define sensor2 A2
#define sensor3 A3
Servo myservo1;
Servo myservo2;
Servo myservo3;
int runTimer = 1; 
int runFor = 30;
void timer();
void setup() {
Serial.begin(9600);
pinMode(remote, INPUT);
pinMode(sensor1, INPUT);
pinMode(sensor2, INPUT);
pinMode(7,OUTPUT);
pinMode(6,OUTPUT);
pinMode(8,OUTPUT);
myservo1.attach(2);
 myservo2.attach(3);
  myservo3.attach(4);
  
}

void loop() {
  int rd1=analogRead(sensor1);
  int rd2= analogRead(sensor2);
  int rd3= analogRead(sensor3);
  int counter =30;
  int positive =0;
  int negative =0;
  int  m=0;
   Serial.println("Game is about to start");
   delay(1000);
   while(true)
   {
   if(m==0)
   {
   Serial.println("Level ONE");
   int n;
  counter =30;
  positive =0;
  negative =0;
   for(n=0; n<20; n++)
  {
  float  a=random(0,30);
  Serial.print(a);
  if(a<10)
  {
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    rd1=analogRead(sensor1);
    rd2= analogRead(sensor2);
    rd3= analogRead(sensor3);
    if(rd1>400 & rd2<400 & rd3<400)
  {
    counter++;
    positive++;
  }
  else 
  {
    counter--;
    negative++;
  }
   delay(300); 
   digitalWrite(6,LOW);
  }
  else if(a>10 & a<20)
  {
    digitalWrite(7,HIGH);
    digitalWrite(6,LOW);
    digitalWrite(8,LOW);
    rd2= analogRead(sensor2);
    rd1=analogRead(sensor1);
    rd3=analogRead(sensor3);
    if(rd2>400 & rd1<400 & rd3<400)
  {
    //Serial.println(rd2);
   counter++;
   positive++;
  }
  else
  {
    counter--;
    negative++;
  }
  delay(300);
digitalWrite(7,LOW);
  }
  
  else if(a>20)
  {
    digitalWrite(8,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(6,LOW);
    rd2= analogRead(sensor2);
    rd1=analogRead(sensor1);
    rd3=analogRead(sensor3);
    if(rd3>400 & rd1<400 & rd3<400)
  {
    //Serial.println(rd2);
   counter++;
   positive++;
  }
  else
  {
    counter--;
    negative++;
  }
  delay(300);
digitalWrite(8,LOW);
  }
  delay(200);
  }
  if(n==20)
  {
    break;
  }
  
   }
   delay(500);
   }
  if(counter>5)
  {
   m++; 
  }
  else
  {
    Serial.println();
    Serial.println(String(counter)+"Positive"+String(positive)+"negative"+String(negative));
    Serial.println("Could Have Been Better");
  }
  
  if(m==1)
  {
    Serial.println("Level Two");
    Serial.println("You Have got 30 seconds for 30 hits!");
     if(runTimer == 1){ 
      lcd.clear();
      Serial.print("TIMER=");
      //Start timer
      timer(); 
   } else {
      Serial.println("over!"); // relay is ON when time expired
      /* *change to LOW if you want the relay to be OFF when the time expired */
   }
   runTimer = 0;
   lcd.noDisplay();
   delay(250);
    
  }
   
  
  Serial.println(String(counter)+"Positive"+String(positive)+"negative"+String(negative));
  delay(300);
  
}
void timer() {
  int counter =20;
  int positive =0;
  int negative =0;
  int rd1=analogRead(sensor1);
 int rd2= analogRead(sensor2);
  int rd3= analogRead(sensor3);
   for(int timer = runFor;timer > 0; --timer){

    Serial.println("Game is about to start");
    delay(2000);
    int n;
  float  a=random(0,30);
  Serial.print(a);
  if(a<10)
  {
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    rd1=analogRead(sensor1);
    rd2= analogRead(sensor2);
    rd3= analogRead(sensor3);
    
    if(rd1>400 & rd2<400 & rd3<400)
  {
    counter++;
    positive++;
  }
  else 
  {
    counter--;
    negative++;
  }
   delay(300); 
   digitalWrite(6,LOW);
  }
  else if(a>10 & a<20)
  {
    digitalWrite(7,HIGH);
    digitalWrite(6,LOW);
    digitalWrite(8,LOW);
    rd2= analogRead(sensor2);
    rd1=analogRead(sensor1);
    rd3=analogRead(sensor3);
    if(rd2>400 & rd1<400 & rd3<400)
  {
    //Serial.println(rd2);
   counter++;
   positive++;
  }
  else
  {
    counter--;
    negative++;
  }
  delay(300);
digitalWrite(7,LOW);
  }
  
  else if(a>20)
  {
    digitalWrite(8,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(6,LOW);
    rd2= analogRead(sensor2);
    rd1=analogRead(sensor1);
    rd3=analogRead(sensor3);
    if(rd3>400 & rd1<400 & rd3<400)
  {
    //Serial.println(rd2);
   counter++;
   positive++;
  }
  else
  {
    counter--;
    negative++;
  }
  delay(300);
digitalWrite(8,LOW);
  }
   if(timer >= 10) {
      //lcd.setCursor(6,0); 
   } else {   
      //lcd.setCursor(6,0);
      Serial.print("0");
      //lcd.setCursor(7,0);
   }
   Serial.println(timer);
   Serial.println(" SECOND!");
   delay(1000);
   
   //lcd.setCursor(0,0);
   //lcd.clear();
   lcd.println(" TIMER ALERT!");  
}
}

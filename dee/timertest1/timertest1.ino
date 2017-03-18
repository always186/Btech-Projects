
#include <LiquidCrystal.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);
int runTimer = 1; 
int runFor = 30; // time in seconds
int buzzerPin = 13;
int relayPin=4;
int data = 0;
 
void setup() {
   pinMode(buzzerPin, OUTPUT);
   pinMode(relayPin,OUTPUT);
   lcd.begin(16, 2);
   Serial.begin(9600);
}
 
void loop() {
   if(runTimer == 1){ 
      digitalWrite(relayPin,LOW); // relay is OFF during countdown
      /* *change to HIGH if you want the relay to be ON while countdowning */
      lcd.clear();
      Serial.print("TIMER=");
      //Start timer
      timer(); 
   } else {
      digitalWrite(relayPin,HIGH); // relay is ON when time expired
      /* *change to LOW if you want the relay to be OFF when the time expired */
   }
   runTimer = 0;
   lcd.noDisplay();
   delay(250);

   lcd.display();
   delay(250);
}
 
void timer() {
   for(int timer = runFor;timer > 0; --timer){
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
   }
   //lcd.setCursor(0,0);
   //lcd.clear();
   lcd.println(" TIMER ALERT!");  
}

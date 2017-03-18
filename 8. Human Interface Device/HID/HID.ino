
#include<Keyboard.h>
#include<SoftwareSerial.h>
#define trigPin 4
#define echoPin 5
#define trigPin1 6
#define echoPin1 7

SoftwareSerial BTSerial(1,2);

int accelero; 

void setup() {
  
  Serial.begin(9600);
  BTSerial.begin(9600);
BTSerial.setTimeout(5);
Serial.setTimeout(5);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);   
    pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);   // servo2 on pin10
}

void loop()
{

  
  if (BTSerial.available()>0)
  {

 long duration, distance;
 
 digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
 
    Serial.print(distance);
    Serial.println(" cm");

      long duration1, distance1;
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;
 
    Serial.print(distance1);
    Serial.println(" cm1");
  
  delay(10);
    accelero = BTSerial.parseInt();
    accelero = map(accelero, 0, 500, 0, 2000);   // mapping the servo2 received value and position range
    Serial.println(accelero);
  if(accelero<800)  
   {  Serial.println(accelero);
            Keyboard.press(char(KEY_UP_ARROW));
//Serial.println("up");

    if(accelero>=70 && accelero<=180)
   {//Serial.println("left");
      //   Keyboard.press(char('l'));

   Keyboard.press(char(KEY_LEFT_ARROW));
         Keyboard.press(char(KEY_UP_ARROW));

   delay(100);
   Keyboard.release(char(KEY_LEFT_ARROW));
   }

    if(accelero>=180 && accelero<=360)
   {//Serial.println("left");
      //   Keyboard.press(char('l'));

   Keyboard.press(char(KEY_LEFT_ARROW));
         Keyboard.press(char(KEY_UP_ARROW));

   delay(150);
   Keyboard.release(char(KEY_LEFT_ARROW));
   }
   
   if(accelero>=440 && accelero<=550)
   {//Serial.println("right");
        // Keyboard.press(char('r'));

      Keyboard.press(char(KEY_RIGHT_ARROW));
        Keyboard.press(char(KEY_UP_ARROW));

      delay(100);
   
      Keyboard.release(char(KEY_RIGHT_ARROW));}

   if(accelero>=550 && accelero<=700)
   {//Serial.println("right");
        // Keyboard.press(char('r'));

      Keyboard.press(char(KEY_RIGHT_ARROW));
        Keyboard.press(char(KEY_UP_ARROW));

      delay(150);
   
      Keyboard.release(char(KEY_RIGHT_ARROW));}
      

   if(accelero>360 && accelero<440)
   {//Serial.println("forward");
      Keyboard.press(char(KEY_UP_ARROW));
      delay(100);
    //  Keyboard.releaseAll();}
   }


if(distance<=20 && distance>0)
{Keyboard.releaseAll();
delay(100);
}

if(distance1<=20 && distance1>0)
{Keyboard.releaseAll();
Keyboard.press(char(KEY_DOWN_ARROW));
delay(1000);
Keyboard.release(char(KEY_DOWN_ARROW));
}
   
   //  Keyboard.releaseAll();

   delay(10);
   
  }
  }

}


// I have designed the code by assuming that the wall is on the left of my bot
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h" 
  #endif        

//i PINS
const int lst=14;
const int lse=15;
const int mst=16;
const int mse=17;
const int rst=18;
const int rse=19;
long d1,d2,d3;

int max_speed=-255, right_speed, left_speed ;
double s=0;
long sensors_sum;
double i;
double Output;

//OUTPUT PINS
const int ml1=10;
const int ml2=11;
const int mr1=12;
const int mr2=13;

void setup() 
{
 Serial.begin(9600);
 pinMode(lst,OUTPUT);
 pinMode(lse,i);
 pinMode(mst,OUTPUT);
 pinMode(mse,i);
 pinMode(rst,OUTPUT);
 pinMode(rse,i);

pinMode(ml1,OUTPUT);
pinMode(ml2,OUTPUT);
pinMode(mr1,OUTPUT);
pinMode(mr2,OUTPUT);

/*Serial.println(" STARTING SETUP");
long st = millis();
while(millis() - st < 10000) //through this loop we are determining the s for 0.1s
{
sensors_read();
s=abs(i)>abs(s)?i:s;
}
Serial.print("s =");
Serial.print(s);
Serial.println(" ");
Serial.println("SETUP DONE");
myPID.SetOutputLimits(-510, 510);
myPID.SetSampleTime(10); //Determines how often the PID algorithm evaluates
myPID.SetMode(AUTOMATIC);*/
}

void loop() 
{
sensors_read(); //Reads sensor values and computes i
if(d1<12 && d2<12 && d3<12)
{
  right_speed=1;
  left_speed=1;
}
else if(d1<12 && d2<12 || d2<12)
{
  right_speed=-1;
  left_speed=1;
}
else if(d3<12 && d2<12)
{
  right_speed=1;
  left_speed=-1;
}
else if(d1<12)
{
  right_speed=-1;
  left_speed=0;
}
else if(d3<12 || d1>17)
{
   right_speed=0;
  left_speed=-1;
}
else
{
right_speed=-1;
  left_speed=-1;  
}
motor_drive();
delay(1);
}

void sensors_read()
{
  digitalWrite(lst, LOW);
  delayMicroseconds(2);
  digitalWrite(lst, HIGH);
  delayMicroseconds(5);
  digitalWrite(lst, LOW);
  d1 = pulseIn(lse, HIGH);
  d1=d1/ 29 / 2;
Serial.print(" d1 = ");
Serial.print(d1);
  digitalWrite(mst, LOW);
  delayMicroseconds(2);
  digitalWrite(mst, HIGH);
  delayMicroseconds(5);
  digitalWrite(mst, LOW);
  d2 = pulseIn(mse, HIGH);
  d2=d2/ 29 / 2;
  Serial.print(" d2 = ");
Serial.print(d2);
digitalWrite(rst, LOW);
  delayMicroseconds(2);
  digitalWrite(rst, HIGH);
  delayMicroseconds(5);
  digitalWrite(rst, LOW);
  d3 = pulseIn(rse, HIGH);
  d3=d3/ 29 / 2;
  Serial.print(" d3 = ");
Serial.println(d3);
//sensors_sum = int(d1+d2); 
//Serial.print(" Sum = ");
//Serial.println(sensors_sum);
//i = int(d1/10);
//Serial.print("i =");
//Serial.println(i);
delay(1); //Set the number to change frequency of readings.
}
void motor_drive()
{ 
  // Drive motors according to the calculated values for a turn
  if(left_speed>0){
    Serial.println("+L");
  digitalWrite(ml1,0);
  digitalWrite(ml2,255);
  }
  else if(left_speed==0){
    Serial.println("0");
  digitalWrite(ml1,0);
  digitalWrite(ml2,0);
  }
  else if(left_speed<0){
    Serial.println("-L");
  digitalWrite(ml1,255);
  digitalWrite(ml2,0);
  }
  if(right_speed>0){
    Serial.println("+R");
  digitalWrite(mr1,0);
  digitalWrite(mr2,255);
  }
  if(right_speed==0){
    Serial.println("0");
  digitalWrite(mr1,0);
  digitalWrite(mr2,0);
  }
  else if(right_speed<0){
    Serial.println("-R");
  digitalWrite(mr1,255);
  digitalWrite(mr2,0);
  }
}

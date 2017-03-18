// I have designed the code by assuming that the wall is on the left of my bot
#include <PID_v1.h>
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h" 
  #endif        

//INPUT PINS
const int lst=2;//left ultrasonic sensor trig pin 
const int lse=3;//left ultrasonic sensor echo pin
//const int mst=4;//middle ultrasonic sensor trig pin
//const int mse=5;//middle ultrasonic sensor echo pin

int max_speed=255, right_speed, left_speed ;
double Setpoint=0;
long sensors_sum;
double Input;
double Output;
double d1,d2;

//OUTPUT PINS
const int ml1=10;
const int ml2=11;
const int mr1=12;
const int mr2=13;

double kp = 5.0;
double ki = 0.55;
double kd = 0.2;

PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);

void setup() 
{
Serial.begin(9600);

pinMode(lst,OUTPUT);
pinMode(lse,INPUT);
//pinMode(mst,OUTPUT);
//pinMode(mse,INPUT);

pinMode(ml1,OUTPUT);
pinMode(ml2,OUTPUT);
pinMode(mr1,OUTPUT);
pinMode(mr2,OUTPUT);

Serial.println(" STARTING SETUP");
long st = millis();
while(millis() - st < 100) //through this loop we are determining the setpoint for 0.1s
{
sensors_read();
Setpoint=abs(Input)>abs(Setpoint)?Input:Setpoint;
}
Serial.print("Setpoint =");
Serial.print(Setpoint);
Serial.println(" ");
Serial.println("SETUP DONE");
myPID.SetOutputLimits(-510, 510);
myPID.SetSampleTime(10); //Determines how often the PID algorithm evaluates
myPID.SetMode(AUTOMATIC);
}

void loop() 
{
sensors_read(); //Reads sensor values and computes Input
myPID.SetTunings(kp, ki, kd);
myPID.Compute();
calc_turn(); //Computes the error to be corrected
motor_drive(); //Sends PWM signals to the motors

delay(1);
}

void sensors_read()
{
  digitalWrite(lst, LOW); 
  delayMicroseconds(2); 
  digitalWrite(lst, HIGH);
  delayMicroseconds(10); 
  digitalWrite(lst, LOW);
  d1 = (pulseIn(lse, HIGH)/58.138)*.39;//answer in inches
  //digitalWrite(mst, LOW); 
  //delayMicroseconds(2); 
  //digitalWrite(mst, HIGH);
  //delayMicroseconds(10); 
  //digitalWrite(mst, LOW);
  //d2 = (pulseIn(mse, HIGH)/58.138)*.39;//answer in inches
//sensors_sum = int(d1 +d2); 
//Input = int(sensors_sum/10);
Input =int (d1/10);
Serial.print("Input =");
Serial.println(Input);
delay(1000); //Set the number to change frequency of readings.
}

void calc_turn()
{ 
 /*Output= k(Setpoint- Input) 
  * setpoint will be when 1 0
  * let setpoint be 1
  * when Input=0 ( 0 0 ) output = 1 --- bot has to move towards left --- left motor -- backward ---- right motor ---- forward
  * when Input=2 ( 1 1 ) output = -1 --- bot has to move towards right --- left motor -- forward ---- right motor ---- backward
  */
 Serial.print("\t Output= ");
 Serial.print(Output);
// If Output is negative calculate right turn speed values
if (Output<=0)
{
right_speed = max_speed + Output;
left_speed = max_speed;
}
// If Output is +ve calculate left turn values
else
{
right_speed = max_speed;
left_speed = max_speed - Output;
}
Serial.print("right_speed =");
Serial.print(right_speed);
Serial.print(" ");
Serial.print("left_speed =");
Serial.print(left_speed);
Serial.println(" ");
delay(1);
}

void motor_drive()
{ 
  // Drive motors according to the calculated values for a turn
  if(left_speed>0){
    Serial.println("+L");
  analogWrite(ml1,0);
  analogWrite(ml2,left_speed);
  }
  else if(left_speed<0){
    Serial.println("-L");
  analogWrite(ml1,(-left_speed));
  analogWrite(ml2,0);
  }
  if(right_speed>0){
    Serial.println("+R");
  analogWrite(mr1,0);
  analogWrite(mr2,right_speed);
  }
  else if(right_speed<0){
    Serial.println("-R");
  analogWrite(mr1,(-right_speed));
  analogWrite(mr2,0);
  }
}

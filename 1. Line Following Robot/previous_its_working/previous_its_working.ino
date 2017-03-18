#include <PID_v1.h>
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h" 
  #endif      

//INPUT PINS
const int ls1=A8;//pins on which sensors have been connected
const int ls2=A9;
const int rs2=A10;
const int rs1=A11;

int max_speed=255, right_speed, left_speed ;
double Setpoint=0;
long sensors_sum;
double Intput;
double Output;

//OUTPUT PINS
const int ml=8;
const int mr=9;

double kp = 0.0;
double ki = 0.0;
double kd = 0.0;

PID myPID(&Intput, &Output, &Setpoint, kp, ki, kd, DIRECT);

void setup()
{
Serial.begin(9600);

 pinMode(ls1,INPUT);
pinMode(ls2,INPUT);
pinMode(rs2,INPUT);
pinMode(rs1,INPUT);

pinMode(ml,OUTPUT);
pinMode(mr,OUTPUT);

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
myPID.SetOutputLimits(-255, 255);
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
}

void sensors_read()
{
sensors_sum = int((-3*analogRead(ls1))+(-1*analogRead(ls2))+(1*analogRead(rs2))+(3*analogRead(rs1))); 
Intput= int(sensors_sum/10);
Serial.print("Input =");
Serial.println(Input);
delay(3000); //Set the number to change frequency of readings.
}
void calc_turn()
{
 /*Output= k(Setpoint- Intput)
  * setpoint will be when 1 0 1
  * let setpoint be 50
  * when left sensor is on black line Intput=0
  * when right sensor is on black line Intput=100
  * so when left sensor is on black line Output=50 ---> +ve ---> we need to move towards left ---> left motor should have lesser speed than right motor
  * and when right sensor is on black line Output= -50 ---> -ve ---> we need to move towards right ---> right motor should have lesser speed than left motor
  */
 Serial.print("\t Output= ");Serial.print(Output);
if (Output< -255)
{
Output = -255;
}
if (Output> 255)
{
Output = 255;
}
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
}

void motor_drive()
{ 
   analogWrite(ml,left_speed);
     analogWrite(mr,right_speed);
}

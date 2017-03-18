#include <PID_v1.h>             

//INPUT PINS
const int ls=A0;//pins on which sensors have been connected
const int ms=A1;
const int rs=A2;

int max_speed=255, right_speed, left_speed ;
double Setpoint=0;
long sensors_average;
long sensors_sum;
double Intput;
double Output;
long a[3] = {0, 0, 0};

//OUTPUT PINS
const int ml1=5;
const int ml2=2;
const int mr1=3;
const int mr2=4;

double kp = 5.0;
double ki = 0.0;
double kd = 0.0;

PID myPID(&Intput, &Output, &Setpoint, kp, ki, kd, DIRECT);

void setup() 
{
Serial.begin(9600);

 pinMode(ls,INPUT);
pinMode(ms,INPUT);
pinMode(rs,INPUT);

pinMode(ml1,OUTPUT);
pinMode(ml2,OUTPUT);
pinMode(mr1,OUTPUT);
pinMode(mr2,OUTPUT);

Serial.println(" STARTING SETUP");
long st = millis();
while(millis() - st < 3000) //through this loop we are determining the setpoint for 3s
{
sensors_read();
if(Intput > Setpoint)
Setpoint=Intput;  
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
sensors_read(); //Reads sensor values and computes sensor sum and weighted average
myPID.SetTunings(kp, ki, kd);
myPID.Compute();
calc_turn(); //Computes the error to be corrected
motor_drive(); //Sends PWM signals to the motors
}

void sensors_read()
{
  sensors_average = 0;
sensors_sum = 0;
a[0]=analogRead(ls);
a[1]=analogRead(ms);
a[2]=analogRead(rs);
for (int i = 0; i < 3; i++)
{
sensors_average += int(a[i] * (i+1) * 1000); 
sensors_sum += int(a[i]); 
}
Intput = int(sensors_average / sensors_sum);
Serial.print("Intput =");
Serial.println(Intput);
delay(1); //Set the number to change frequency of readings.
}

void calc_turn()
{ 
 /*Output= k(Setpoint- Intput) 
  * setpoint will be when 1 0 1
  * let setpoint be 50
  * when left sensor is on black line Intput=0
  * when right sensor is on black line Intput=100
  * so when left sensor is on black line error value=50 ---> +ve ---> we need to move towards left ---> left motor should have lesser speed than right motor
  * and when left sensor is on black line error value= -50 ---> -ve ---> we need to move towards right ---> right motor should have lesser speed than left motor
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
if (Output< 0)
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
{ // Drive motors according to the calculated values for a turn
  analogWrite(ml1,0);
   analogWrite(ml2,left_speed);
    analogWrite(mr1,0);
     analogWrite(mr2,right_speed);
}

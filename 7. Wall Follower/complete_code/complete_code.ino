/*
 * 1 -> setup for lfr
 * 2 -> motion for lfr
 * 3 -> setup1 for a for wfr --- when wall is on right
 * 4 -> setup1 for b for wfr
 * 5 -> motion1 for wfr
 * 6 -> setup2 for a for wfr --- when wall is on left
 * 7 -> setup2 for b for wfr
 * 8 -> motion2 for wfr
*/
#include <PID_v1.h>
#if ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h" 
  #endif        

#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {30, 31, 32, 33}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {34, 35, 36, 37}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//INPUT PINS
const int ls1=A8;//pins on which sensors have been connected 
const int ls2=A9;
const int rs2=A10;
const int rs1=A11;

int max_speed, right_speed, left_speed ;
double Setpoint=0;
long sensors_sum;
double Input;
double Output;

//OUTPUT PINS
const int ml1=10;
const int ml2=11;
const int mr1=12;
const int mr2=13;

const int lst=14;
const int lse=15;
const int mst=16;
const int mse=17;
const int rst=18;
const int rse=19;

double kp = 5.0;
double ki = 0.0;
double kd = 0.0;

long a=0,b=0,d1=0,d2=0,d3=0;

PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);

void setup() 
{
Serial.begin(9600);

pinMode(ls1,INPUT);
pinMode(ls2,INPUT);
pinMode(rs2,INPUT);
pinMode(rs1,INPUT);

pinMode(ml1,OUTPUT);
pinMode(ml2,OUTPUT);
pinMode(mr1,OUTPUT);
pinMode(mr2,OUTPUT);

pinMode(lst,OUTPUT);
 pinMode(lse,INPUT);
 pinMode(mst,OUTPUT);
 pinMode(mse,INPUT);
 pinMode(rst,OUTPUT);
 pinMode(rse,INPUT);
 
myPID.SetOutputLimits(-510, 510);
myPID.SetSampleTime(10); //Determines how often the PID algorithm evaluates
myPID.SetMode(AUTOMATIC);
}

void loop() 
{

  char customKey = customKeypad.getKey();

  switch(customKey)
  {
    
    
    case '1': 
Serial.println(" STARTING SETUP");
    while(customKey!='#')
    {
      setup1();
      customKey = customKeypad.getKey();
    }
    Serial.print("Setpoint =");
Serial.print(Setpoint);
Serial.println(" ");
Serial.println("SETUP DONE"); 
    break;
    
    
    case '2': 
    max_speed=255;
    while(customKey!='#')
    {
     sensors_read1(); //Reads sensor values and computes Input
myPID.SetTunings(kp, ki, kd);
myPID.Compute();
calc_turn(); //Computes the error to be corrected
motor_drive(); //Sends PWM signals to the motors 
    }
    break;
    
    
    case '3': 
    a=0;
Serial.println(" STARTING SETUP");
    while(customKey!='#')
    {
      setup2();
      customKey = customKeypad.getKey();
    }
    Serial.print("a =");
Serial.print(a);
Serial.println(" ");
Serial.println("SETUP DONE"); 
    break;
    
    
    case '4': 
    b=0;
Serial.println(" STARTING SETUP");
    while(customKey!='#')
    {
      setup3();
      customKey = customKeypad.getKey();
    }
    Serial.print("b =");
Serial.print(b);
Serial.println(" ");
Serial.println("SETUP DONE"); 
    break;
    
    
    case '5': 
    max_speed=-255;
    while(customKey!='#')
    {
      sensors_read2();
      wf1();
motor_drive2();
      customKey = customKeypad.getKey();
    }
    break;
    
    
    case '6': 
    a=0;
Serial.println(" STARTING SETUP");
    while(customKey!='#')
    {
      setup4();
      customKey = customKeypad.getKey();
    }
    Serial.print("a =");
Serial.print(a);
Serial.println(" ");
Serial.println("SETUP DONE"); 
    break;
   
    
    case '7': 
    b=0;
Serial.println(" STARTING SETUP");
    while(customKey!='#')
    {
      setup5();
      customKey = customKeypad.getKey();
    }
    Serial.print("b =");
Serial.print(b);
Serial.println(" ");
Serial.println("SETUP DONE"); 
    break;


    case '8': 
    max_speed=-255;
    while(customKey!='#')
    {
      sensors_read2();
      wf2();
motor_drive2();
      customKey = customKeypad.getKey();
    }
    break;

        
  }
  delay(1);
}

void setup1()
{
sensors_read1();
Setpoint=abs(Input)>abs(Setpoint)?Input:Setpoint;
Serial.print("Setpoint =");
Serial.print(Setpoint);
Serial.println(" ");
}
void setup2()
{
sensors_read2();
a=d1>a?d1:a;
Serial.print("a =");
Serial.print(a);
Serial.println(" ");
}
void setup3()
{
sensors_read2();
b=d1>b?d1:b;
Serial.print("b =");
Serial.print(b);
Serial.println(" ");
}
void setup4()
{
sensors_read2();
a=d3>a?d3:a;
Serial.print("a =");
Serial.print(a);
Serial.println(" ");
}
void setup5()
{
sensors_read2();
b=d3>b?d3:b;
Serial.print("b =");
Serial.print(b);
Serial.println(" ");
}
void sensors_read1()
{
sensors_sum = int((-3*analogRead(ls1))+(-1*analogRead(ls2))+(1*analogRead(rs2))+(3*analogRead(rs1))); 
Input = int(sensors_sum/10);
Serial.print("Input =");
Serial.println(Input);
delay(1); //Set the number to change frequency of readings.
}
void sensors_read2()
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
delay(1); //Set the number to change frequency of readings.
}

void wf1()
{
 if(d1>=a && d1<=b)
{
  right_speed=-1;
  left_speed=-1;
}
else if(d1>b || d1==0)
{
  right_speed=-1;
  left_speed=0;
}
else if(d1<a)
{
  right_speed=0;
  left_speed=-1;
}
else if(d2<a)
{
  right_speed=-1;
  left_speed=1;
}
delay(1); 
}

void wf2()
{
 if(d3>=a && d3<=b)
{
  right_speed=-1;
  left_speed=-1;
}
else if(d3>b || d3==0)
{
  right_speed=0;
  left_speed=-1;
}
else if(d1<a)
{
  right_speed=-1;
  left_speed=0;
}
else if(d2<a)
{
  right_speed=1;
  left_speed=-1;
}
delay(1);  
}

void calc_turn()
{ 
 /*Output= k(Setpoint- Input) 
  * setpoint will be when 1 0 1
  * let setpoint be 50
  * when left sensor is on black line Input=0
  * when right sensor is on black line Input=100
  * so when left sensor is on black line Output=50 ---> +ve ---> we need to move towards left ---> left motor should have lesser speed than right motor
  * and when right sensor is on black line Output= -50 ---> -ve ---> we need to move towards right ---> right motor should have lesser speed than left motor
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
void motor_drive2()
{ 
  // Drive motors according to the calculated values for a turn
  if(left_speed>0){
    Serial.println("+L");
  analogWrite(ml1,0);
  analogWrite(ml2,255);
  }
  else if(left_speed<0){
    Serial.println("-L");
  analogWrite(ml1,255);
  analogWrite(ml2,0);
  }
  if(right_speed>0){
    Serial.println("+R");
  analogWrite(mr1,0);
  analogWrite(mr2,255);
  }
  else if(right_speed<0){
    Serial.println("-R");
  analogWrite(mr1,255);
  analogWrite(mr2,0);
  }
}

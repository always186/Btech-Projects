#include <PID_v1.h>             
double Setpoint, Input, Output;
double kp = 0.1;
double ki = 0.0;
double kd = 0.0;
PID myPID(&Input, &Output, &Setpoint, kp, ki, kd, DIRECT);
boolean cwccw; //Boolean Data Type holds values that can be only True or False
byte pin_sensor[2] = {A0,A1};  /*array for 2 sensors connected on pins A0 and A1. Data type byte: Holds unsigned 8-bit (1-byte) integers that range in value from 0 through 255. Use the Byte data type to contain binary data.The default value of Byte is 0.*/
int val_sensor[2] = {0,0};     //array to store value of sensors
byte pin_sig[2][2] = {         //a matrix for the 4 pins on which motor is connected
{10,9},                      //motor0 : pin10,9 PWM+LOW or LOW+PWM → CW or 
{5,6}                        //motor1 : pin 5,6 PWM+LOW or LOW+PWM → CW or CCW
};
boolean f_right;           
int power = 40;            
int val_max;               
int val_min = 2046;        
boolean monitor = true;    //on/off
boolean m_stop = false;    //on/off
#define led_0 2 //first led connected on digital pin 2
#define led_1 3 //second led connected on digital pin 3
void setup() 
{
Serial.begin(115200);
pinMode(pin_sensor[0], INPUT); //sensor pins
pinMode(pin_sensor[1], INPUT);
pinMode(pin_sig[0][0], OUTPUT); //motor pins        
pinMode(pin_sig[0][1], OUTPUT);         
pinMode(pin_sig[1][0], OUTPUT);         
pinMode(pin_sig[1][1], OUTPUT);         
pinMode(led_0, OUTPUT);               //LED pins
pinMode(led_1, OUTPUT);

digitalWrite(led_0, HIGH); //marks the beginning of configuration period for sensors
digitalWrite(led_1, HIGH);
long st = millis();
while(millis() - st < 3000) //through this loop we are determining the min and max sum of the values of 2 sensors 
{
val_sensor[0] = analogRead(pin_sensor[0]);
val_sensor[1] = analogRead(pin_sensor[1]);
if(val_sensor[0] + val_sensor[1] < val_min)
{
val_min = val_sensor[0] + val_sensor[1];   
}
if(val_sensor[0] + val_sensor[1] > val_max)
{
val_max = val_sensor[0] + val_sensor[1];   
}
}
Serial.println("");
Serial.println(val_min);
Serial.println(val_max);
delay(2000);
digitalWrite(led_0, LOW);
digitalWrite(led_1, LOW); //marks the end of configuration period for sensors

myPID.SetOutputLimits(0, power);
myPID.SetSampleTime(10); //Determines how often the PID algorithm evaluates
Input = 0;
Setpoint = val_max;
myPID.SetMode(AUTOMATIC);
motor(0, 50, false); //assigns ccwc = false and motor 1 starts moving with pwm=50 in 1 direction    
delay(1000);
motor_stop(0,0); //this will stop the motor 1
motor(1, 50, false);    //assigns ccwc = false and motor 2 starts moving with pwm=50 in 1 direction   
delay(1000);
motor_stop(1,0); //this will stop the motor 2
delay(1000);
}
void loop() 
{
if(Serial.available())
{
ser_rcv();
myPID.SetTunings(kp, ki, kd);
myPID.SetOutputLimits(0, power);
}
for(byte i=0;i < 2;i++){                              
val_sensor[i] = analogRead(pin_sensor[i]);
}
int val_diff = val_sensor[0] - val_sensor[1];
int val_sum = val_sensor[0] + val_sensor[1];
Input = val_sum;
myPID.Compute();
if(val_sum > val_max / 2 && val_diff > 0){
f_right = true;
}
else if(val_sum > val_max / 2 && val_diff <= 0)
{
f_right = false;
}
if(f_right == true){                                  
digitalWrite(led_0, HIGH);
motor(0, power - Output, false);                    
motor(1, power, false);                             
digitalWrite(led_0, LOW);
}
else{                                                 
digitalWrite(led_1, HIGH);
motor(0, power, false);                             
motor(1, power - Output, false);                    
digitalWrite(led_1, LOW);
}
if(monitor == true){
Serial.print(val_sensor[0]);
Serial.print("\t");
Serial.print(val_sensor[1]);
Serial.print("\t");
Serial.print(val_diff);             //val_sensor[0] - val_sensor[1]
Serial.print("\t");
Serial.print(val_sum);              //val_sensor[0] + val_sensor[1]
Serial.print("\t");
Serial.print(f_right);
Serial.print("\t");
Serial.print(power);                
Serial.print("\t");
Serial.print(Output);               
Serial.print("\t");
Serial.print(power - Output);       
Serial.print("\t");
Serial.print(kp, 2);                //Kp
Serial.print("\t");
Serial.print(ki, 2);                //Ki
Serial.print("\t");
Serial.print(kd, 2);                //Kd
Serial.print("\t");
Serial.println("");
}
}
void motor(byte num, byte pw, boolean cw)
{
pw = map(pw, 0, 100, 0, 255);
if(m_stop == false) //if motor is moving
{
if(cwccw != cw) /*it checks if the motor is currently moving in the opposite direction to the indicated direction and if it is so then it stops  the motor (num)*/
{
digitalWrite(pin_sig[num][0],LOW);
digitalWrite(pin_sig[num][1],LOW);
delay(1);
}
if(cw == true) //assigns the pwm value(pw) to the motor(num) in the one direction
{
cwccw = true;
analogWrite(pin_sig[num][0], pw);
analogWrite(pin_sig[num][1], 0);
}
else ////assigns the pwm value(pw) to the motor(num) in the one direction
{
cwccw = false;
analogWrite(pin_sig[num][0], 0);
analogWrite(pin_sig[num][1], pw);
}
}
else //if motor is not moving
{
motor_stop(0, 0);
motor_stop(1, 0);
}
}
void motor_stop(byte num,int dur)
{
digitalWrite(pin_sig[num][0],LOW);
digitalWrite(pin_sig[num][1],LOW);
if(dur >0){
delay(dur);
}
}
void ser_rcv()
{
float k_step = 0.01;
char c = Serial.read();
if(c == 'q') //Kp +
{              
kp += k_step;
}
else if(c == 'a') //Kp -
{        
kp -= k_step;
if(kp < 0)
{
kp = 0;
}
}
else if(c == 'w') //Ki +
{         
ki += k_step;
}
else if(c == 's'){         //Ki -
ki -= k_step;
if(ki < 0)
{
ki = 0;
}
}
else if(c == 'e') //Kd +
{         
kd += k_step;
}
else if(c == 'd') //Kd -
{         
kd -= k_step;
if(kd < 0)
{
kd = 0;
}
}
else if(c == 'r') //motor power +
{         
power += 5;
if(power > 100){
power = 100;
}
}
else if(c == 'f') //motor power -
{         
power -= 5;
if(power < 0){
power = 0;
}
}
else if(c == 'z'){         //serial monitor output on/off
monitor = !monitor;
}
else if(c == 'x'){         //motor on/off
m_stop = !m_stop;
}
}



const int ls=A0;//pins on which sensors have been connected
const int ms=A1;
const int rs=A2;
int max_speed=255, right_speed, left_speed, last_proportional=0, proportional , integral, derivative, set_point=0, error_value;//we have to declare this value in the begining as per our requirement
int sensors_average = 0;
int sensors_sum = 0;
int position;
long a[3] = {0, 0, 0};
int Kp=5, Ki=0, Kd=0; 
const int ml1=5;
const int ml2=2;
const int mr1=3;
const int mr2=4;
int rms;/*declaring the speed of right motor. speed of motor can be between 0 to 255 only. Put the speeds less than 255 only because at maximum speed the chances of deviation are more because sensors need time for proper detection*/ 
int lms;//declaring the speed of left motor
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
}
void loop()
{ 
sensors_read(); //Reads sensor values and computes sensor sum and weighted average
pid_calc(); //Calculates position[set point] and computes Kp,Ki and Kd
calc_turn(); //Computes the error to be corrected
motor_drive(right_speed, left_speed); //Sends PWM signals to the motors
}
void sensors_read()
{
  a[0]=analogRead(ls);
a[1]=analogRead(ms);
a[2]=analogRead(rs);
for(int i=0;i<3;i++)
{
Serial.print(a[i]);
Serial.print(' ');
}
Serial.println(' ');
for (int i = 0; i < 3; i++)
{
sensors_average += a[i] * i * 1000; 
sensors_sum += int(a[i]); 
}
position = int(sensors_average / sensors_sum);
Serial.print("sensors_average =");
Serial.print(sensors_average);
Serial.print(' ');
Serial.print("sensors_sum =");
Serial.print(sensors_sum);
Serial.print(' ');
Serial.print("position =");
Serial.print(position);//this is the value of set point
Serial.println();
delay(1500); //Set the number to change frequency of readings.
}
void pid_calc()
{
//position = int(sensors_average / sensors_sum);
proportional = position-set_point; // Replace set_point by your set point. setpoint is basically the position we calculated using the code snippet pid2
integral = integral + proportional;
derivative = proportional - last_proportional;
last_proportional = proportional;
error_value = int(proportional * Kp + integral * Ki + derivative * Kd);
Serial.print("error_value= ");
Serial.print(error_value);
Serial.println(" ");
}
void calc_turn()
{ //Restricting the error value between +256.
if (error_value< -255)
{
error_value = -255;
}
if (error_value> 255)
{
error_value = 255;
}
// If error_value is less than zero calculate right turn speed values
if (error_value< 0)
{
right_speed = max_speed + error_value;
left_speed = max_speed;
}
// If error_value is greater than zero calculate left turn values
else
{
right_speed = max_speed;
left_speed = max_speed - error_value;
}
Serial.print("right_speed =");
Serial.print(right_speed);
Serial.print(" ");
Serial.print("left_speed =");
Serial.print(left_speed);
Serial.println(" ");
}
void motor_drive(int rms, int lms)
{ // Drive motors according to the calculated values for a turn
  analogWrite(ml1,0);
   analogWrite(ml2,lms);
    analogWrite(mr1,0);
     analogWrite(mr2,rms);
}

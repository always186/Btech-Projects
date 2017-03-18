/*this code give the readings when all sensors are on the correct position that is in the center of line. 
Basically, it gives the setpoint for all 5 sensors.
so we have to coustmize the code as per our no. of sensors.
the number of the analog input pin are 0 to 15 on the Mega 
the pid code uses the analog value.
analog pins always give values between 0 to 1023 
 */  

const int s1=A0;//pins on which sensors have been connected
const int s2=A1;
const int s3=A2;
/*const int s4=5;
const int s5=6;
const int s6=7;
const int s7=8;
const int s8=9;
const int s9=10;*/
long sensors_average;
int sensors_sum;
int position;
long a[3];//array to store values of sensors 
void setup()
{ 
Serial.begin(9600); //Necessary to set up Serial port
pinMode(s1,INPUT);
pinMode(s2,INPUT);
pinMode(s3,INPUT);
/*pinMode(s4,INPUT);
pinMode(s5,INPUT);
pinMode(s6,INPUT);
pinMode(s7,INPUT);
pinMode(s8,INPUT);
pinMode(s9,INPUT);*/
}
void loop()
{
sensors_average = 0;
sensors_sum = 0;
a[0]=analogRead(s1);
a[1]=analogRead(s2);
a[2]=analogRead(s3);
/*a[3]=analogRead(s4);
a[4]=analogRead(s5);
a[5]=analogRead(s6);
a[6]=analogRead(s7);
a[7]=analogRead(s8);
a[8]=analogRead(s9);*/
for(int i=0;i<9;i++)
{
Serial.print(a[i]);
Serial.print(' ');
}
Serial.println(' ');
for (int i = 0; i < 5; i++)
{
sensors_average += a[i] * i * 1000; //Calculating the weighted mean
sensors_sum += int(a[i]); //Calculating sum of sensor readings
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
delay(2); //Set the number to change frequency of readings.
}

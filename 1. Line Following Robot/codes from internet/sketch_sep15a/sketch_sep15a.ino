#include <QTRSensors.h>
#include <IRremote.h>

#define NUM_SENSORS             8 
#define NUM_SAMPLES_PER_SENSOR  4  
#define EMITTER_PIN             QTR_NO_EMITTER_PIN  

QTRSensorsAnalog qtra((unsigned char[]) {7,6,0,1,2,3,4,5},NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, EMITTER_PIN);

unsigned int sensorValues[NUM_SENSORS];

int Kp=1;
int Ki=0.011;
int Kd=5.3;

int MOTOR1_PIN1 = 6; //viteza
int MOTOR1_PIN2 = 5; //directie

int MOTOR2_PIN1 = 10; //viteza
int MOTOR2_PIN2 = 9; //directie

int RECV_PIN = 4;

IRrecv irrecv(RECV_PIN);

decode_results results;

unsigned int last_proportional = 0;
long integral = 0;
int buton = 0;
int buttonState = 0;
int ir=1;
int power_difference;
int max = 255;
int rc=0;
int a=0;
int b=0;
int c=0;

int x=0;


void button()
{
  buttonState = digitalRead(3);
  if((buttonState == LOW)&&(buton==0))   
  {
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    delay(300); 
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    delay(300); 
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    delay(300); 
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    delay(300); 
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    delay(1000); 

    buton=1;
    
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
  }
}



void stop()
{
  digitalWrite(MOTOR1_PIN1, LOW);
  digitalWrite(MOTOR1_PIN2, LOW);
  digitalWrite(MOTOR2_PIN1, LOW);
  digitalWrite(MOTOR2_PIN2, LOW);
}

void set_motors(int a, int b)
{
  if(a==0)
  {
    digitalWrite(MOTOR1_PIN1, LOW);
  digitalWrite(MOTOR1_PIN2, LOW);
  }

  if(b==0)
  {
    digitalWrite(MOTOR2_PIN1, LOW);
  digitalWrite(MOTOR2_PIN2, LOW);
  }

  if(a>0)
  {
    analogWrite(MOTOR1_PIN1, a);
    digitalWrite(MOTOR1_PIN2, LOW);
  }

  if(b>0)
  {
    analogWrite(MOTOR2_PIN1, b);
    digitalWrite(MOTOR2_PIN2, LOW);
  }

  if(a<0)
  {
    analogWrite(MOTOR1_PIN1, 255+a);
    digitalWrite(MOTOR1_PIN2, HIGH);
  }

  if(b<0)
  {
    analogWrite(MOTOR2_PIN1, 255+b);
    digitalWrite(MOTOR2_PIN2, HIGH);
  }
}

void rcvd()
{  
    if (irrecv.decode(&results)) 
  {
   switch (results.value)
    {
    case 0x5821 : ir=0; //stop
      break;
    case 0x1421 : ir=1;
      break;
/*    case 0x1121 : stop();//stop
      break; 
    case 0x5121 : stop();//stop
      break; 
*/
    
    
    }
   irrecv.resume(); // Receive the next value
  }
}


void driver(int power_difference,int buton, int ir)
{

  if((power_difference < 0)&&(buton==1)&&(ir==1))     
  {
    set_motors(max+power_difference,max);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
  }
  if((power_difference > 0)&&(buton==1)&&(ir==1))   
  {
    set_motors(max,max-power_difference);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
  }
  if((power_difference == 0)&&(buton==1)&&(ir==1))    
  {
    set_motors(max,max); 
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
  }
  if(ir==0)
  {
    stop(); 
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
  }
}

/*int distanta()
{
  
  digitalWrite(13, LOW);
  delayMicroseconds(2);
  digitalWrite(13, HIGH);
  delayMicroseconds(10);
  digitalWrite(13, LOW);
  int duration = pulseIn(12, HIGH);
  int cm = duration / 29 / 2;
  return cm;
  
}*/

void setup() {
//  Serial.begin(9600); 
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  
  pinMode(8, OUTPUT); //led motor stanga
  
  pinMode(7, OUTPUT); //led motor dreapta 
  
  //pinMode(2, OUTPUT); indicator calibrare:led motor ambele aprinse
  

  pinMode(3, INPUT_PULLUP); //buton start
  
//  pinMode(3, INPUT); //buton start
//  digitalWrite(3, HIGH); //buton start pull-up
  
  pinMode(4, INPUT); //ir sensor
  
  //pinMode(12, INPUT); senzor obstacol
 // pinMode(13, OUTPUT); senzor obstacol
  
  
  delay(1000);

irrecv.enableIRIn(); 

  int i;

  digitalWrite(7, HIGH);   // turn on LED to indicate we are in calibration mode
  digitalWrite(8, HIGH);   // turn on LED to indicate we are in calibration mode
  for (i = 0; i < 60; i++)  // make the calibration take about 10 seconds
  {
    qtra.calibrate();       // reads all sensors 10 times at 2.5 ms per six sensors (i.e. ~25 ms per call)
    delay(20);
  }   
  digitalWrite(7, LOW);     // turn off LED to indicate we are through with calibration
  digitalWrite(8, LOW);     // turn off LED to indicate we are through with calibration
  delay(1500);


}


void loop() {


  rcvd();
  
  
  unsigned int position = qtra.readLine(sensorValues);
 
  int proportional = ((int)position) - 3500;   
 
 
 // Serial.println(position);

//  delay(200);
  int derivative = proportional - last_proportional;
  integral += proportional;
  last_proportional = proportional;
  int power_difference = proportional*Kp + integral*Ki + derivative*Kd; //2.5 10000 35
  const int max = 255;
  if(power_difference > max)
    power_difference = max;
  if(power_difference < -max)
    power_difference = -max; 
    
  button();
  
//  cm=distanta();

  driver(power_difference,buton,ir);
  
  
}







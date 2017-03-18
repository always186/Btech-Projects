#define LSensor1 3
#define LSensor2 4
#define LSensor3 5
#define LSensor4 6
#define LSensor5 A0
#define LSensor6 A1
#define LSensor7 A2
#define LSensor8 A3

#define motor_L1 7
#define motor_R1 8
#define pwm1 9
#define pwm2 10
#define motor_L2 11
#define motor_R2 12

// Variable for line checking
int Position=0, correctPosition=15, totalPosition=0;
int error=0, lastError=0;
int timerZero=0, timeStopA=0, timeStopB=0;

// Variable for PID
int integral=0;
int derivative=0;
int turn,turn_L,turn_R;

// debounce time for line checking
unsigned long timeLSensor, debounceDelayLSensor = 15;

// Setup the robot to move 15s.
unsigned long timeToStop = 15000; 

void setup()
{
  pinMode(LSensor1,INPUT);
  pinMode(LSensor2,INPUT);
  pinMode(LSensor3,INPUT);
  pinMode(LSensor4,INPUT);
  pinMode(LSensor5,INPUT);
  pinMode(LSensor6,INPUT);
  pinMode(LSensor7,INPUT);
  pinMode(LSensor8,INPUT);
  pinMode(motor_L1,OUTPUT);
  pinMode(motor_R1,OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(motor_L2,OUTPUT);
  pinMode(motor_R2,OUTPUT);
  
  timeLSensor = millis();
  
  Serial.begin(9600);
  Serial.println("SETUP DONE");
}


void loop()
{  
  if (millis() > timeToStop) // Stop the motor after 15s.
  {
    StopRun();// Stop the motors.
    /*
    Serial.print("pwm1 : ");
    Serial.println("0");
    Serial.print("pwm2 : ");
    Serial.println("0");
    Serial.println("MOTOR STOPPED");
    */
    //while(1); // The loop end.
  }  
    else
    lineFollower(5,10,30,50,40); // Make the robot track to the line if it is not the time to stop
    }
    
void lineFollower(int Kp, int Ki, int Kd, int speed_L, int speed_R) // Make the robot track to the line using the pid parameters and the speed of two motors.
{
  lineCheck(); // Check the position of the robot.
  PID(Kp,Ki,Kd); // Using PID calculate the error.
  go_Straight(speed_L + turn_L, speed_R - turn_R); // Robot go straight.
}

void lineCheck() // Check the position of the robot.
{
  // Check line for every 15ms.
  if ( millis() - timeLSensor >= debounceDelayLSensor )
  {
    // Take the reading of 8 line IR sensor.
    int s = digitalRead(LSensor1);
    int t = digitalRead(LSensor2);
    int u = digitalRead(LSensor3);
    int v = digitalRead(LSensor4); 
    int w = digitalRead(LSensor5);
    int x = digitalRead(LSensor6);
    int y = digitalRead(LSensor7);
    int z = digitalRead(LSensor8);
    
   lastError=error; // Calculate the position of the robot.
    
       if (s==0 && t==0 && u==0 && v==0 && w==0 && x==0 && y==0 && z==0)  // if no line is detected.
    {      
      if (timeStopB > 0)// Setup a timer
      {
        timerZero += timeStopA - timeStopB ;   
      }     
      timeStopB = timeStopA;
      timeStopA = millis();  
     if (lastError == 0)
      {
        /*StopRun();
        Serial.println("***Stop***");*/
        Position = 15;
      }     
      while (timerZero > 1500) // Robot stops when it away from line more than 3 second.
      {
        StopRun();
      }
      }        
    else // When line is detected.    
    {      
      timerZero=0, timeStopA=0, timeStopB=0; // Reset the timer when it detects the line again.
      
      // Calculate the position of the robot.
      totalPosition = s + t + u + v + w + x + y + z;
      
      Position = int(( 2*s + 8*t + 12*u + 14*v + 16*w + 18*x + 22*y + 28*z ) / totalPosition);
    }    
    timeLSensor = millis();
    error = Position - correctPosition;
        /* 
    Serial.print("Position : "); // Show value of position on laptop.
    Serial.println(Position);
    Serial.print("lastError : "); // Show value of last position on laptop.
    Serial.println(lastError);
    Serial.print("error : "); // Show value of error on laptop.
    Serial.println(error);
    Serial.println("------------");*/
  }
}
void PID(int Kp, int Ki, int Kd) // Using PID calculate the error.
{
    //---PID---
    // For P
    error = error; 
    /*
    Serial.print(Position), Serial.print(" ;    ");
    Serial.print(error), Serial.print(" ;    ");
    Serial.print(lastError), Serial.println(" ;    ");
    */
    
    // For I
    
    // For remains the same integral error value. (error = last error)
    integral += error;
    integral = constrain(integral,0,100);

    /* For error of position changed. 
       E.g. last time error is 2, now error is one. */
    if ( error != lastError ) 
    { /*
      // For +ve position value.
      if ( Position > 0 )
      {
        if ( Position > lastPosition )  // away from the line.
          integral = 0;  
       else
          integral = 0;  // towards to the line.
      }
      
      // For -ve position value.
      else if ( Position < 0 )
      {
        if ( Position < lastPosition )  // away from the line.
          integral = 0;
         
        else
          integral = 0;  // towards to the line.
      }
      
      // For position value is 0.
      else*/
        integral = 0;
    }
    
      
    // For D
    derivative = error - lastError;
    
    /*
    Serial.print("Error_P : "); // Show value of error P on laptop.
    Serial.println(error);
    Serial.print("Error_I : "); // Show value of error I on laptop.
    Serial.println(integral);
    Serial.print("Error_D : "); // Show value of error D on laptop.
    Serial.println(derivative);
    */
    
    
  // Sum of the error of PID + encoder
  turn = (Kp*error + Ki*integral/10 + Kd*derivative);
  turn = constrain(turn,-100,100);
  
  // Make turn1 & turn2 only have -ve value.
  // +turn1 & -turn2
  turn_L = constrain(turn,-100,0);
  turn_R = constrain(turn,0,100);

  /*
  Serial.print("Turn : "); // Show value of turn on laptop.
  Serial.println(turn);
  Serial.println(" ");
  */
}

void go_Straight(int speedL, int speedR)// Robot go straight.
{
  Forward();
  speedL = speed_Map(speedL);
  speedR = speed_Map(speedR);
  analogWrite(pwm1,speedL);
  analogWrite(pwm2,speedR);
  /*
  Serial.println("*Go Straight*");
  Serial.print("pwm1 : ");
  Serial.println(speedL);
  Serial.print("pwm2 : ");
  Serial.println(speedR);*/
}


// Robot reverse.
void go_Reverse(int speedL, int speedR)
{
  Backward();
  
  speedL = speed_Map(speedL);
  speedR = speed_Map(speedR);
  analogWrite(pwm1,speedL);
  analogWrite(pwm2,speedR);
  /*
  Serial.println("*Go Backward*");
  Serial.print("pwm1 : ");
  Serial.println(speedL);
  Serial.print("pwm2 : ");
  Serial.println(speedR);*/
}


// Robot rotate left.
void self_Rotate_Left(int speedL, int speedR)
{
  rotateLeft();
  
  speedL = speed_Map(speedL);
  speedR = speed_Map(speedR);
  analogWrite(pwm1,speedL);
  analogWrite(pwm2,speedR);
  /*
  Serial.println("*Rotate Left*");
  Serial.print("pwm1 : ");
  Serial.println(speedL);
  Serial.print("pwm2 : ");
  Serial.println(speedR);*/
}


// Robot rotate right.
void self_Rotate_Right(int speedL, int speedR)
{
  rotateRight();
  
  speedL = speed_Map(speedL);
  speedR = speed_Map(speedR);
  analogWrite(pwm1,speedL);
  analogWrite(pwm2,speedR);
  /*
  Serial.println("*Rotate Right*");
  Serial.print("pwm1 : ");
  Serial.println(speedL);
  Serial.print("pwm2 : ");
  Serial.println(speedR);*/
}


// Convert speed in the range of 0 - 100.
int speed_Map(int speed_Motor)
{
  speed_Motor = constrain(speed_Motor,0,100);
  speed_Motor = map(speed_Motor,0,100,0,255);

  return speed_Motor;
}
  

// Setup the motors to move forward.  
void Forward()
{
  digitalWrite(motor_L1,HIGH);   // Move forward.
  digitalWrite(motor_R1,LOW);
  digitalWrite(motor_L2,LOW);    // Move forward.
  digitalWrite(motor_R2,HIGH);
}


// Setup the motors to move backward. 
void Backward()
{
  digitalWrite(motor_L1,LOW);    // Move backward.
  digitalWrite(motor_R1,HIGH);
  digitalWrite(motor_L2,HIGH);   // Move backward.
  digitalWrite(motor_R2,LOW);
}


// Setup motors to turn left.
void rotateLeft()
{
  digitalWrite(motor_L1,LOW);    // Move backward.
  digitalWrite(motor_R1,HIGH);
  digitalWrite(motor_L2,LOW);    // Move forward.
  digitalWrite(motor_R2,HIGH);
}
  

// Setup motors to turn right.
void rotateRight()
{
  digitalWrite(motor_L1,HIGH);    // Move forward.
  digitalWrite(motor_R1,LOW);
  digitalWrite(motor_L2,HIGH);    // Move backward.
  digitalWrite(motor_R2,LOW);
}


// Stop the motors.
void StopRun()
{
  digitalWrite(pwm1,0);
  digitalWrite(pwm2,0);
  delay(100);
  
  digitalWrite(motor_L1,LOW);
  digitalWrite(motor_R1,LOW);
  digitalWrite(motor_L2,LOW);
  digitalWrite(motor_R2,LOW);
}


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

//INPUT PINS
const int ls1=51;//pins on which sensors have been connected 
const int ls2=49;
const int rs2=47;
const int rs1=45;

//OUTPUT PINS
const int ml1=10;
const int ml2=11;
const int mr1=12;
const int mr2=13;

int right_speed=0, left_speed=0;

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
}

void loop() 
{
  if(digitalRead(ls1)==1 && digitalRead(ls2)==1  && digitalRead(rs1)==1  && digitalRead(rs2)==1 || digitalRead(ls1)==1 && digitalRead(ls2)==0  && digitalRead(rs1)==0  && digitalRead(rs2)==1 || digitalRead(ls1)==0 && digitalRead(ls2)==0  && digitalRead(rs1)==0  && digitalRead(rs2)==0)
{
  right_speed=1;
  left_speed=1;
}
else if(digitalRead(ls1)==1 && digitalRead(ls2)==0  && digitalRead(rs1)==1  && digitalRead(rs2)==1)
{
  right_speed=1;
  left_speed=0;
}
else if(digitalRead(ls1)==0 && digitalRead(ls2)==0  && digitalRead(rs1)==1  && digitalRead(rs2)==1 || digitalRead(ls1)==0 && digitalRead(ls2)==0  && digitalRead(rs1)==0  && digitalRead(rs2)==1)
{
  right_speed=1;
  left_speed=-1;
}
else if(digitalRead(ls1)==1 && digitalRead(ls2)==1  && digitalRead(rs1)==0  && digitalRead(rs2)==1)
{
  right_speed=0;
  left_speed=1;
}
else if(digitalRead(ls1)==1 && digitalRead(ls2)==1  && digitalRead(rs1)==0  && digitalRead(rs2)==0 || digitalRead(ls1)==1 && digitalRead(ls2)==0  && digitalRead(rs1)==0  && digitalRead(rs2)==0)
{
  right_speed=-1;
  left_speed=1;
}
motor_drive2();
  delay(1);
}

void motor_drive2()
{ 
  // Drive motors according to the calculated values for a turn
  if(left_speed==1){
    Serial.println("+L");
  analogWrite(ml1,0);
  analogWrite(ml2,200);
  }
  else if(left_speed==-1){
    Serial.println("-L");
  analogWrite(ml1,200);
  analogWrite(ml2,0);
  }
  else if(left_speed==0){
    Serial.println("0");
  analogWrite(ml1,0);
  analogWrite(ml2,0);
  }
  if(right_speed==1){
    Serial.println("+R");
  analogWrite(mr1,0);
  analogWrite(mr2,200);
  }
  else if(right_speed==-1){
    Serial.println("-R");
  analogWrite(mr1,200);
  analogWrite(mr2,0);
  }
  else if(right_speed==0){
    Serial.println("0");
  analogWrite(mr1,0);
  analogWrite(mr2,0);
  }
}

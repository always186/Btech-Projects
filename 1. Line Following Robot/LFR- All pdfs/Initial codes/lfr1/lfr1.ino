/*ir sensor readings are always a number between 0 and 1023*/
const int li=A0;
const int mi=A1;
const int ri=A2;
const int ml1=5;
const int ml2=2;
const int mr1=3;
const int mr2=4;
const int rms=255;/*declaring the speed of right motor. speed of motor can be between 0 to 255 only. Put the speeds less than 255 only because at maximum speed the chances of deviation are more because sensors need time for proper detection*/ 
const int lms=255;//declaring the speed of left motor
void setup() {
Serial.begin(9600);
pinMode(li,INPUT);
pinMode(mi,INPUT);
pinMode(ri,INPUT);
pinMode(ml1,OUTPUT);
pinMode(ml2,OUTPUT);
pinMode(mr1,OUTPUT);
pinMode(mr2,OUTPUT);
}

void loop() {
int  ls=digitalRead(li);
   int ms=digitalRead(mi);
   int rs=digitalRead(ri);
     Serial.print("ls="); 
    Serial.print(ls);
    Serial.print("\t ms=");
    Serial.print(ms);
    Serial.print("\t rs=");
    Serial.println(rs);
 while(!(ls==1  && ms==1 && rs==1))//i had to put some loop one or other. please check if it is valid all the time or not
  {
    ls=digitalRead(li);
   ms=digitalRead(mi);
    rs=digitalRead(ri);
    Serial.print("ls="); 
    Serial.print(ls);
    Serial.print("\t ms=");
    Serial.print(ms);
    Serial.print("\t rs=");
    Serial.println(rs);
    if(ls==1 && ms==0 && rs==1) //go front
 {
  Serial.println("go front");
  analogWrite(ml1,0);
   analogWrite(ml2,lms);
    analogWrite(mr1,0);
     analogWrite(mr2,rms);
 }
 else if(ls==0 && ms==1 && rs==1) //turn left
 {
   Serial.println("turn left");
  analogWrite(ml1,0);
   analogWrite(ml2,lms);
    analogWrite(mr1,0);
     analogWrite(mr2,0);
 }
else if(ls==1 && ms==1 && rs==0) //turn right
 {
  Serial.println("turn right");
  analogWrite(ml1,0);
   analogWrite(ml2,0);
    analogWrite(mr1,0);
     analogWrite(mr2,rms);
 }
 else if(ls==0 && ms==0 && rs==1) //right angle towards left
 {
  Serial.println("right angle towards left");
  analogWrite(ml1,lms);
   analogWrite(ml2,0);
    analogWrite(mr1,0);
     analogWrite(mr2,rms);
 }
  else if(ls==1 && ms==0 && rs==0) //right angle towards right
 {
  Serial.println("right angle towards right");
  analogWrite(ml1,0);
   analogWrite(ml2,lms);
    analogWrite(mr1,rms);
     analogWrite(mr2,0);
 }
 delay(1);
  }
  delay(1000);
}

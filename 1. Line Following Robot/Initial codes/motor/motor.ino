const int ml1=10;
const int ml2=11;
const int mr1=12;
const int mr2=13;
/*const int ml=8;
const int mr=9;*/
void setup() {
  // put your setup code here, to run once:
pinMode(ml1,OUTPUT);
pinMode(ml2,OUTPUT);
pinMode(mr1,OUTPUT);
pinMode(mr2,OUTPUT);
//pinMode(ml,OUTPUT);
//pinMode(mr,OUTPUT);
}

void loop() {
 // digitalWrite(ml1,HIGH);
 // digitalWrite(mr1,HIGH);
analogWrite(ml1,0);
analogWrite(ml2,255);
delay(3000);
analogWrite(ml2,0);
analogWrite(ml1,255);
delay(3000);
analogWrite(ml2,0);
analogWrite(ml1,0);
analogWrite(mr1,0);
analogWrite(mr2,255);
delay(3000);
\
analogWrite(mr2,0);
analogWrite(mr1,255);
delay(3000);
analogWrite(mr2,0);
analogWrite(mr1,0);
}

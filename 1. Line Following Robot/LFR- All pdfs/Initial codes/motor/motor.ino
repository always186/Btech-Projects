int a=0;
const int ml1=10;
const int ml2=11;
const int mr1=12;
const int mr2=13;
void setup() {
  // put your setup code here, to run once:
pinMode(ml1,OUTPUT);
pinMode(ml2,OUTPUT);
pinMode(mr1,OUTPUT);
pinMode(mr2,OUTPUT);
}

void loop() {
while(a<10000000)
 {
analogWrite(ml1,0);
analogWrite(ml2,255);
analogWrite(mr1,0);
     analogWrite(mr2,255);
a++;
}
}

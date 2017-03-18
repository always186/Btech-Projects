const int ml1=10;
const int ml2=11;
const int mr1=12;
const int mr2=13;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

pinMode(ml1,OUTPUT);
pinMode(ml2,OUTPUT);
pinMode(mr1,OUTPUT);
pinMode(mr2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(ml2,HIGH);
digitalWrite(ml1,LOW);
digitalWrite(mr2,HIGH);
digitalWrite(mr2,LOW);
}

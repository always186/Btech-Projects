const int lst=10;
const int lse=A0;
const int mst=11;
const int mse=A1;
const int rst=12;
const int rse=A2;
long d1,d2,d3;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(lst,OUTPUT);
 pinMode(lse,INPUT);
 pinMode(mst,OUTPUT);
 pinMode(mse,INPUT);
 pinMode(rst,OUTPUT);
 pinMode(rse,INPUT);
}

void loop() {
  digitalWrite(lst, LOW);
  delayMicroseconds(2);
  digitalWrite(lst, HIGH);
  delayMicroseconds(5);
  digitalWrite(lst, LOW);
  d1 = pulseIn(lse, HIGH);
  d1=d1/ 29 / 2;
Serial.print(" d1 = ");
Serial.print(d1);
  digitalWrite(mst, LOW);
  delayMicroseconds(2);
  digitalWrite(mst, HIGH);
  delayMicroseconds(5);
  digitalWrite(mst, LOW);
  d2 = pulseIn(mse, HIGH);
  d2=d2/ 29 / 2;
  Serial.print(" d2 = ");
Serial.print(d2);
digitalWrite(rst, LOW);
  delayMicroseconds(2);
  digitalWrite(rst, HIGH);
  delayMicroseconds(5);
  digitalWrite(rst, LOW);
  d3 = pulseIn(rse, HIGH);
  d3=d3/ 29 / 2;
  Serial.print(" d3 = ");
Serial.println(d3);
delay(5);
}

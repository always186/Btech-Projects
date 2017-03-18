int d;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    analogWrite(4,Serial.read());
       analogWrite(5,Serial.read());
       analogWrite(6,Serial.read());
       analogWrite(7,Serial.read());
       analogWrite(12,Serial.read());
       analogWrite(10,Serial.read());
       analogWrite(11,Serial.read()); 
}
}

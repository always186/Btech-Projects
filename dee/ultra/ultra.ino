const int trig=2;
const int echo=3;
double d1,cm,dur;
void setup() {
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trig,LOW);
  delayMicroseconds(2); 
digitalWrite(trig,HIGH);
  delayMicroseconds(10); 
digitalWrite(trig,LOW);  
dur=pulseIn(echo, HIGH);
      cm=dur/29/2; 
         Serial.println("in cm =");
    Serial.println(cm);

delay(1000);
}


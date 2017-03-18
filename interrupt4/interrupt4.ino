const int trig=7;
const int echo=8;
double d1,cm,dur;
#define white 3
#define red 4
#define yellow 5

int state=0;
void setup() {
  Serial.begin(9600);
  pinMode(white,OUTPUT);
pinMode(red,OUTPUT);
pinMode(yellow,OUTPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(2,OUTPUT);
  // put your setup code here, to run once:
attachInterrupt(digitalPinToInterrupt(2),shake,CHANGE);
}

void loop() {
digitalWrite(white,HIGH);
digitalWrite(red,HIGH);
digitalWrite(trig,LOW);
delayMicroseconds(2); 
digitalWrite(trig,HIGH);
delayMicroseconds(10); 
digitalWrite(trig,LOW);  
dur=pulseIn(echo, HIGH);
      cm=dur/29/2; 
         Serial.println("in cm =");
    Serial.println(cm);
    if(cm<15)
    {
      
      state=!state;
      digitalWrite(2,state);
    }
   



}
void shake()
{
  digitalWrite(yellow,1);
  delay(100);
  digitalWrite(yellow,0);
  delay(100);
}


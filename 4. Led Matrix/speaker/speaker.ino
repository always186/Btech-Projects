
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2,OUTPUT);
   pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
     pinMode(6,INPUT);
      pinMode(7,INPUT);
       pinMode(8,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int b,a=0;
  for(int i=0;i<11;i++)
  {
   
  b=floor(random(2,5));
  Serial.println(b);
digitalWrite(b,HIGH);
if(digitalRead(b+4))
a++;
Serial.println(a);
delay(500);
digitalWrite(b,LOW);
  }
Serial.println("Your Final Score is: "+ a);
delay(10000);
}

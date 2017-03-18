
#define remote A0
#define sensor1 A1
#define sensor2 A2


void setup() {
  Serial.begin(9600);
  pinMode(remote, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  
}

void loop() {
  int rd1=analogRead(sensor1);
  int rd2= analogRead(sensor2);
  int counter =10;
  int positive =0;
  int negative =0;
  while(true)
  {
    Serial.println("Game is about to start");
    delay(2000);
    int n;
  for(n=0; n<20; n++)
  {
  float  a=random()*100;
  //Serial.print(a*100);
  if(a<0.5)
  {
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    rd1=analogRead(sensor1);
    rd2= analogRead(sensor2);
    
    if(rd1>400 & rd2<400)
  {
    counter++;
    positive++;
  }
  else
  {
    counter--;
    negative++;
  }
   delay(300); 
   digitalWrite(6,LOW);
  }
  else
  {
    digitalWrite(7,HIGH);
    digitalWrite(6,LOW);
    rd2= analogRead(sensor2);
    rd1=analogRead(sensor1);
    if(rd2>400 & rd1<400)
  {
    //Serial.println(rd2);
   counter++;
   positive++;
  }
  else
  {
    counter--;
    negative++;
  }
  delay(300);
digitalWrite(7,LOW);
  }
  delay(200);
  }
  if(n==20)
  {
    break;
  }
  }
  Serial.println(String(counter)+"Positive"+String(positive)+"negative"+String(negative));
  delay(300);
  
}

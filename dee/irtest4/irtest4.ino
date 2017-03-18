
#define remote A0
#define sensor1 A1
#define sensor2 A2
#define sensor3 A3

void setup() {
  Serial.begin(9600);
  pinMode(remote, INPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
   pinMode(8,OUTPUT);
  
}

void loop() {
  int rd1=analogRead(sensor1);
  int rd2= analogRead(sensor2);
  int rd3= analogRead(sensor3);
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
  float  a=random(0,30);
  Serial.print(a);
  if(a<10)
  {
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    rd1=analogRead(sensor1);
    rd2= analogRead(sensor2);
    rd3= analogRead(sensor3);
    
    if(rd1>400 & rd2<400 & rd3<400)
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
  else if(a>10 & a<20)
  {
    digitalWrite(7,HIGH);
    digitalWrite(6,LOW);
    digitalWrite(8,LOW);
    rd2= analogRead(sensor2);
    rd1=analogRead(sensor1);
    rd3=analogRead(sensor3);
    if(rd2>400 & rd1<400 & rd3<400)
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
  
  else if(a>20)
  {
    digitalWrite(8,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(6,LOW);
    rd2= analogRead(sensor2);
    rd1=analogRead(sensor1);
    rd3=analogRead(sensor3);
    if(rd3>400 & rd1<400 & rd3<400)
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
digitalWrite(8,LOW);
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

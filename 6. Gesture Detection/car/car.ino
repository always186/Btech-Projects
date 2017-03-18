//-----------------------------------------------MEGA MASTER-------------------------------------//



void setup() {
  pinMode(8,OUTPUT);
  pinMode(A12,INPUT);//left
  pinMode(A13,INPUT);//forward
  pinMode(A14,INPUT);//right
   pinMode(A15,INPUT);//stop
   pinMode(A11,INPUT);//back
   Serial.begin(9600);
// put your setup code here, to run once:

}

void loop() {
//Serial.println(analogRead(A12));
  digitalWrite(8,HIGH);

  if(analogRead(A15)>1000 )
  {
  Serial.write("s");}
  
  if(analogRead(A12)>1000 )
  {
  Serial.write("l");}

    
  if(analogRead(A14)>1000 )
  {
  Serial.write("r");}
  
  if(analogRead(A13)>1000 )
  {
  Serial.write("f");}

  if(analogRead(A11)>1000 )
  {
  Serial.write("b");}

  
delay(500);
  // put your main code here, to run repeatedly:

}

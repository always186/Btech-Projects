

int accelero; 

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5);
  //servo1.attach(9);                                  // servo1 on pin9
 // servo2.attach(10);                                 // servo2 on pin10
}

void loop()
{
  if (Serial.available())
  {
    accelero = Serial.parseInt();
     accelero = map(accelero, 0, 500, 0, 2000);   // mapping the servo2 received value and position range
     Serial.println(accelero);
  }
}


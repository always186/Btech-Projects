/*ir sensor readings are always a number between 0 and 1023*/
const int s1 = 2; //pins on which sensors have been connected
const int s2 = 3;
const int s3 = 4;
const int s4 = 5;
const int s5 = 6;
const int s6 = 7;
const int s7 = 8;
const int s8 = 9;
const int s9 = 10;
const int ml1 = 5; //pins on which motor pins are connected
const int ml2 = 2;
const int mr1 = 3;
const int mr2 = 4;
const int rms = 190; /*declaring the speed of right motor. speed of motor can be between 0 to 255 only. Put the speeds less than 255 only because at maximum speed the chances of deviation are more because sensors need time for proper detection*/
const int lms = 170; //declaring the speed of left motor
long a;
void setup()
{
  Serial.begin(9600);
  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(s5, INPUT);
  pinMode(s6, INPUT);
  pinMode(s7, INPUT);
  pinMode(s8, INPUT);
  pinMode(s9, INPUT);
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
}

void loop() {
  a = (digitalRead(s1) * 100000000) + (digitalRead(s2) * 10000000) + (digitalRead(s3) * 1000000) + (digitalRead(s4) * 100000) + (digitalRead(s5) * 10000) + (digitalRead(s6) * 1000) + (digitalRead(s7) * 100) + (digitalRead(s8) * 10) + (digitalRead(s9) * 1);
      Serial.println(a);
  while (!(a == 111111111)) //I had to put some loop one or other. please check if it is valid all the time or not example if there is a big white break grater than 3 cm.....well there you can simply increase the distance between your front sensor and the sensor line from 3 cm as per the length of the gap
  {
    a = (digitalRead(s1) * 100000000) + (digitalRead(s2) * 10000000) + (digitalRead(s3) * 1000000) + (digitalRead(s4) * 100000) + (digitalRead(s5) * 10000) + (digitalRead(s6) * 1000) + (digitalRead(s7) * 100) + (digitalRead(s8) * 10) + (digitalRead(s9) * 1);
        Serial.println(a);
    if (a == 011111111) //turn sharply to the left
    {
      Serial.println("turn sharply to the left");
      analogWrite(ml1, 0);
      analogWrite(ml2, lms);
      analogWrite(mr1, 0);
      analogWrite(mr2, rms);
    }
    else if (a == 001111111 || a == 100111111 || a == 110011111 || a == 111001111 || a == 000111111 || a == 100011111 || a == 110001111 || a == 11001011 || a == 10001011) //turn left or obtuse angled turn towards left
    {
      Serial.println("turn left or obtuse angled turn towards left");
      analogWrite(ml1, 0);
      analogWrite(ml2, 0);
      analogWrite(mr1, 0);
      analogWrite(mr2, rms);
    }
   else if (a == 111000111 || a == 111010111 || a == 111101111 || a == 000010000 || a == 000000000) //go front or there is a break in the line either black or white
    {
      Serial.println("go front or there is a break in the line");
      analogWrite(ml1, 0);
      analogWrite(ml2, lms);
      analogWrite(mr1, 0);
      analogWrite(mr2, rms);
    }
    else if (a == 111100111 || a == 111110011 || a == 111111001 || a == 111111100 || a == 111111000 || a == 111110001 || a == 111100011 || a == 111010011 || a == 111010001) //turn right or obtuse angled turn towards right
    {
      Serial.println("turn right or obtuse angled turn towards right");
      analogWrite(ml1, 0);
      analogWrite(ml2, lms);
      analogWrite(mr1, 0);
      analogWrite(mr2, 0);
    }
   else if (a == 111111110) //turn sharply to the right
    {
      Serial.println("turn sharply to the right");
      analogWrite(ml1, 0);
      analogWrite(ml2, lms);
      analogWrite(mr1, 0);
      analogWrite(mr2, rms);
    }
    else if (a == 000010111 || a == 000011111 || a == 000001111 || a == 000000111) //right angle towards left
    {
      Serial.println("right angle towards left");
      analogWrite(ml1, lms);
      analogWrite(ml2, 0);
      analogWrite(mr1, 0);
      analogWrite(mr2, rms);
    }
    else if (a == 111010000 || a == 111110000 || a == 111100000 || a == 111000000) //right angle towards right
    {
      Serial.println("right angle towards right");
      analogWrite(ml1, 0);
      analogWrite(ml2, lms);
      analogWrite(mr1, rms);
      analogWrite(mr2, 0);
    }
     else if (a == 011000111 || a == 001000111 || a == 000000111 || a == 100000111) //acute angle towards left or acute angle intersection towards left but yet i want it to move forward
    {
      Serial.println("acute angle towards left or acute angle intersection towards left but yet i want it to move forward");
      analogWrite(ml1, 0);
      analogWrite(ml2, lms);
      analogWrite(mr1, 0);
      analogWrite(mr2, rms);
    }
    else if (a == 110000111) //acute angle towards left or acute angle intersection towards left
    {
       a = (digitalRead(s1) * 100000000) + (digitalRead(s2) * 10000000) + (digitalRead(s3) * 1000000) + (digitalRead(s4) * 100000) + (digitalRead(s5) * 10000) + (digitalRead(s6) * 1000) + (digitalRead(s7) * 100) + (digitalRead(s8) * 10) + (digitalRead(s9) * 1);
      Serial.println(a);
      if(a==111010111)
      {
      Serial.println("acute angle towards left");
      analogWrite(ml1, lms);
      analogWrite(ml2, 0);
      analogWrite(mr1, 0);
      analogWrite(mr2, rms);
      }
      else if(a==111000011)
      {
      Serial.println("acute angle intersection towards left");
      analogWrite(ml1, 0);
      analogWrite(ml2, lms);
      analogWrite(mr1, 0);
      analogWrite(mr2, rms);
      }
      else if (a == 011000111 || a == 001000111 || a == 000000111 || a == 100000111) //acute angle towards right or acute angle intersection towards right but yet i want it to move forward
    {
      Serial.println("acute angle towards right or acute angle intersection towards right but yet i want it to move forward");
      analogWrite(ml1, 0);
      analogWrite(ml2, lms);
      analogWrite(mr1, 0);
      analogWrite(mr2, rms);
    }
    else if (a == 110000111) //acute angle towards right or acute angle intersection towards right
    {
       a = (digitalRead(s1) * 100000000) + (digitalRead(s2) * 10000000) + (digitalRead(s3) * 1000000) + (digitalRead(s4) * 100000) + (digitalRead(s5) * 10000) + (digitalRead(s6) * 1000) + (digitalRead(s7) * 100) + (digitalRead(s8) * 10) + (digitalRead(s9) * 1);
      Serial.println(a);
      if(a==111010111)
      {
      Serial.println("acute angle towards left");
      analogWrite(ml1, lms);
      analogWrite(ml2, 0);
      analogWrite(mr1, 0);
      analogWrite(mr2, rms);
      }
      else if(a==111000011)
      {
      Serial.println("acute angle intersection towards left");
       analogWrite(ml1, 0);
      analogWrite(ml2, lms);
      analogWrite(mr1, 0);
      analogWrite(mr2, rms);
      }
    }
    delay(1);
  }
  delay(1000);
}}

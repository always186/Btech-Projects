#include <LedControl.h>

int DIN = 12;
int CS =  11;
int CLK = 10;
byte s[8]=       {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
byte hi[8]=      {0x00,0x00,0x4A,0x4A,0x7A,0x4A,0x4A,0x00};
byte neutral[8]= {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C};
byte blinke[8]=  {0x00,0x60,0x66,0x00,0x00,0x42,0x3C,0x00};
byte smile[8]=   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
byte sad[8]=     {0x00,0x66,0x66,0x00,0x00,0x3C,0x42,0x81};
byte esmile[8]=  {0x00,0x42,0xA5,0x00,0x00,0x42,0x3C,0x00};
byte neutrale[8]= {0x00,0x66,0x66,0x00,0x00,0x00,0x7E,0x00};
byte eneutral[8]={0x00,0x00,0x66,0x00,0x00,0x00,0x7E,0x00};
byte frown[8]=   {0x42,0x24,0x18,0x42,0x00,0x00,0x3C,0x42};
byte face[8]=    {0x42,0xE7,0x42,0x18,0x99,0x42,0x3C,0x00};
byte ok[8]=      {0x00,0xE9,0xAA,0xAC,0xAC,0xAA,0xE9,0x00};
byte bye[8]=     {0x08,0x1C,0x1E,0x5E,0x3E,0x1E,0x1E,0x0C};
byte kiss[8]={0x00, 0x66, 0x66, 0x00, 0x08, 0x1C, 0x08, 0x00};
byte heart[8]={0x00, 0x0C, 0x52, 0xB1, 0x82, 0x44, 0x28, 0x10};
byte heart2[8]={0x00, 0x0C, 0x5E, 0xFF, 0xFE, 0x7C, 0x38, 0x10};
byte u[8]={0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x7E, 0x00};
LedControl lc=LedControl(DIN,CLK,CS,0);

void setup(){
 lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,15);      // Set the brightness to maximum value
 lc.clearDisplay(0);         // and clear the display
}

void loop(){ 
initial();  
 printByte(hi);
delay(2000);
  faces();
wheel();
lc.clearDisplay(0);
delay(2000);
}
void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}
void faces()
{
byte h[8]= {0x00,0x66,0x66,0x66,0x00,0x00,0x00,0x00};
  printByte(h);
  delay(1000);
  h[1]=0x00;
  h[2]=0x00;
  printByte(h);
  delay(1000);
  h[3]=0x00;
  h[2]=0x44;
  printByte(h);
  delay(1000);
  h[2]=0x22;
  printByte(h);
  delay(1000);
  h[2]=0x44;
  printByte(h);
  delay(1000);
  h[2]=0x22; 
  printByte(h);
  delay(1000);
  h[2]=0x44;
  printByte(h);
  delay(1000);   
  byte h1[8]= {0x00,0x00,0x66,0x66,0x00,0x00,0x42,0x3C};
  printByte(h1);
  delay(1000);
  h1[6]=0x7E;
  printByte(h1);
  delay(1000);
  welcome();
  h1[6]=0x3C;
  h1[7]=0x08;
  printByte(h1);
  delay(200);
  h1[7]=0x10;
  printByte(h1);
  delay(200);
  h1[7]=0x08;
  printByte(h1);
  delay(200);
 h1[7]=0x10;
  printByte(h1);
  delay(200);
  h1[7]=0x08;
  printByte(h1);
  delay(200);
  h1[7]=0x10;
  printByte(h1);
  delay(200);
  h1[7]=0x08;
  printByte(h1);
  delay(200);
  h1[7]=0x10;
  printByte(h1);
  delay(200);
  h1[7]=0x08;
  printByte(h1);
  delay(200);
  h1[7]=0x10;
  printByte(h1);
  delay(200);
  h1[7]=0x08;
  printByte(h1);
  delay(200);
  printByte(blinke);
  delay(1500);
   printByte(sad);
  delay(1500);
   printByte(frown);
  delay(1500);
    printByte(neutrale);
  delay(1500);
  printByte(eneutral);
  delay(1500);
   printByte(kiss);
  delay(1500);
  printByte(face);
  delay(1500);
  printByte(ok);
  delay(1500);
  printByte(bye);
  delay(1500);
 printByte(heart);
  delay(1500);
   printByte(heart2);
  delay(1500);
   printByte(u);
  delay(1500);
}
void welcome()
{
byte w[8]= {0x00, 0x42, 0x42, 0x42, 0x5A, 0x66, 0x42, 0x00};
printByte(w);
  delay(500);
  byte e[8]= {0x00, 0x3E, 0x20, 0x20, 0x38, 0x20, 0x3E, 0x00};
printByte(e);
  delay(500);
  byte l[8]= {0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7C, 0x00};
printByte(l);
  delay(500);
  byte c[8]= {0x00, 0x7C, 0x40, 0x40, 0x40, 0x40, 0x7C, 0x00};
printByte(c);
  delay(500);
  byte o[8]= {0x00, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x7E, 0x00};
printByte(o);
  delay(500);
  byte m[8]= {0x00, 0x42, 0x66, 0x5A, 0x42, 0x42, 0x42, 0x00};
printByte(m);
  delay(500);
printByte(e);
  delay(1000);
}
void initial()
{
  int i;
  byte a[8]= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  for(i=0;i<8;i++)
  {
    a[i]=0x80;
    printByte(a);
  delay(65);
  }
  byte a1[8]= {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xC0};
  printByte(a1);
  delay(65);
  byte a2[8]= {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xE0};
  printByte(a2);
  delay(65);
  byte a3[8]= {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xF0};
  printByte(a3);
  delay(65);
  byte a4[8]= {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xF8};
  printByte(a4);
  delay(65);
  byte a5[8]= {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFC};
  printByte(a5);
  delay(65);
  byte a6[8]= {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFE};
  printByte(a6);
  delay(65);
  byte a7[8]= {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF};
  printByte(a7);
  delay(65);
  byte a8[8]= {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xFF};
  for(i=6;i>=0;i--)
  {
    a8[i]=0x81;
    printByte(a8);
  delay(65);
  }
   byte a9[8]= {0x83,0x81,0x81,0x81,0x81,0x81,0x81,0xFF};
  printByte(a9);
  delay(65);
   byte a10[8]= {0x87,0x81,0x81,0x81,0x81,0x81,0x81,0xFF};
  printByte(a10);
  delay(65);
   byte a11[8]= {0x8F,0x81,0x81,0x81,0x81,0x81,0x81,0xFF};
  printByte(a11);
  delay(65);
   byte a12[8]= {0x9F,0x81,0x81,0x81,0x81,0x81,0x81,0xFF};
  printByte(a12);
  delay(65);
 byte a13[8]= {0xBF,0x81,0x81,0x81,0x81,0x81,0x81,0xFF};
 printByte(a13);
  delay(65);
 byte a14[8]= {0xFF,0x81,0x81,0x81,0x81,0x81,0x81,0xFF};
 printByte(a14);
  delay(65);
 byte a15[8]= {0xFF,0x81,0x81,0x81,0x81,0x81,0x81,0xFF};
 printByte(a15);
  delay(65);
  for(i=1;i<7;i++)
  {
    a15[i]=0xC1;
    printByte(a15);
  delay(65);
  }
   byte a16[8]= {0xFF,0xC1,0xC1,0xC1,0xC1,0xC1,0xE1,0xFF};
  printByte(a16);
  delay(65);
   byte a17[8]= {0xFF,0xC1,0xC1,0xC1,0xC1,0xC1,0xF1,0xFF};
  printByte(a17);
  delay(65);
   byte a18[8]= {0xFF,0xC1,0xC1,0xC1,0xC1,0xC1,0xF9,0xFF};
  printByte(a18);
  delay(65);
   byte a19[8]= {0xFF,0xC1,0xC1,0xC1,0xC1,0xC1,0xFD,0xFF};
  printByte(a19);
  delay(65);
 byte a20[8]= {0xFF,0xC1,0xC1,0xC1,0xC1,0xC1,0xFF,0xFF};
 printByte(a20);
  delay(65);
 for(i=5;i>0;i--)
  {
    a20[i]=0xC3;
    printByte(a20);
  delay(65);
  }
  byte a21[8]= {0xFF,0xC7,0xC3,0xC3,0xC3,0xC3,0xFF,0xFF};
 printByte(a21);
  delay(65);
  byte a22[8]= {0xFF,0xCF,0xC3,0xC3,0xC3,0xC3,0xFF,0xFF};
 printByte(a22);
  delay(65);
  byte a23[8]= {0xFF,0xDF,0xC3,0xC3,0xC3,0xC3,0xFF,0xFF};
 printByte(a23);
  delay(65);
  byte a24[8]= {0xFF,0xFF,0xC3,0xC3,0xC3,0xC3,0xFF,0xFF};
 printByte(a24);
  delay(65);
  for(i=2;i<6;i++)
  {
    a24[i]=0xE3;
    printByte(a24);
  delay(65);
  }
  byte a25[8]= {0xFF,0xFF,0xE3,0xE3,0xE3,0xF3,0xFF,0xFF};
 printByte(a25);
  delay(65);
  byte a26[8]= {0xFF,0xFF,0xE3,0xE3,0xE3,0xFB,0xFF,0xFF};
 printByte(a26);
  delay(65);
  byte a27[8]= {0xFF,0xFF,0xE3,0xE3,0xE3,0xFF,0xFF,0xFF};
 printByte(a27);
  delay(65);
  for(i=4;i>1;i--)
  {
    a27[i]=0xE7;
    printByte(a27);
  delay(65);
  }
   byte a28[8]= {0xFF,0xFF,0xEF,0xE7,0xE7,0xFF,0xFF,0xFF};
 printByte(a28);
  delay(65);
  byte a29[8]= {0xFF,0xFF,0xFF,0xE7,0xE7,0xFF,0xFF,0xFF};
 printByte(a29);
  delay(65);
  for(i=3;i<5;i++)
  {
    a29[i]=0xF7;
    printByte(a29);
  delay(65);
  }
   byte a30[8]= {0xFF,0xFF,0xFF,0xF7,0xFF,0xFF,0xFF,0xFF};
 printByte(a30);
  delay(65);
   byte a31[8]= {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
 printByte(a31);
  delay(500);
  printByte(s);
  delay(1000);
}
void wheel()
{
byte l[8]= {0x10,0x10,0x10,0xFE,0x10,0x10,0x10,0x00};
  byte l1[8]= {0x82,0x44,0x28,0x10,0x28,0x44,0x82,0x00};
  byte l2[8]= {0x92,0x54,0x38,0xFE,0x38,0x54,0x92,0x00};
  byte l3[8]= {0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0x00};
  byte l4[8]= {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
  printByte(l);
  delay(50); 
  printByte(l1);
  delay(50);
  printByte(l2);
  delay(50);  
  printByte(l3);
  delay(50); 
  printByte(l2);
  delay(50);
  printByte(l1);
  delay(50); 
  printByte(l);
  delay(50);  printByte(l);
  delay(50); 
  printByte(l1);
  delay(50);
  printByte(l2);
  delay(50);  
  printByte(l3);
  delay(50); 
  printByte(l2);
  delay(50);
  printByte(l1);
  delay(50); 
  printByte(l);
  delay(50);  printByte(l);
  delay(50); 
  printByte(l1);
  delay(50);
  printByte(l2);
  delay(50);  
  printByte(l3);
  delay(50); 
  printByte(l2);
  delay(50);
  printByte(l1);
  delay(50); 
  printByte(l);
  delay(50);  printByte(l);
  delay(50); 
  printByte(l1);
  delay(50);
  printByte(l2);
  delay(50);  
  printByte(l3);
  delay(50); 
  printByte(l2);
  delay(50);
  printByte(l1);
  delay(50); 
  printByte(l);
  delay(50);  printByte(l);
  delay(50); 
  printByte(l1);
  delay(50);
  printByte(l2);
  delay(50);  
  printByte(l3);
  delay(50); 
  printByte(l2);
  delay(50);
  printByte(l1);
  delay(50); 
  printByte(l);
  delay(50);  printByte(l);
  delay(50); 
  printByte(l1);
  delay(50);
  printByte(l2);
  delay(50);  
  printByte(l3);
  delay(50); 
  printByte(l2);
  delay(50);
  printByte(l1);
  delay(50); 
  printByte(l);
  delay(50);  printByte(l);
  delay(50); 
  printByte(l1);
  delay(50);
  printByte(l2);
  delay(50);  
  printByte(l3);
  delay(50); 
  printByte(l2);
  delay(50);
  printByte(l1);
  delay(50); 
  printByte(l);
  delay(50); 
  printByte(l3);
  delay(50); 
  printByte(l4);
  delay(1000);
}




void screenDisplay() {
  byte row = B10000000;
 
  for (byte k = 0; k < 8; k++) {
    // Open up the latch ready to receive data
    digitalWrite(latchPin, LOW);
 
    shiftData(~row);
    shiftData(~led[k]);
    // Close the latch, sending the data in the registers out to the matrix
    digitalWrite(latchPin, HIGH);
    row = row >> 1;
  }
}
 
void shiftData(byte data) {
  // Shift out 8 bits LSB first,
  // on rising edge of clock
  boolean pinState;
 
  //clear shift register read for sending data
  digitalWrite(dataPin, LOW);
 
  // for each bit in dataOut send out a bit
  for (int i=0; i<8; i++) 
  {
    //set clockPin to LOW prior to sending bit
    digitalWrite(clockPin, LOW);
 
    // if the value of data and (logical AND) a bitmask
    // are true, set pinState to 1 (HIGH)
    if (data & (1<<i)) 
    {
      pinState = HIGH;
    }
    else 
    {
      pinState = LOW;
    }
 
    //sets dataPin to HIGH or LOW depending on pinState
    digitalWrite(dataPin, pinState);
 
    //send bit out on rising edge of clock
    digitalWrite(clockPin, HIGH);
    digitalWrite(dataPin, LOW);
  }
 
  //stop shifting
  digitalWrite(clockPin, LOW);
}

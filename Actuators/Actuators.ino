#include <SoftwareSerial.h>
SoftwareSerial HeadSerial = SoftwareSerial(53, 3);
SoftwareSerial LeftElbowSerial = SoftwareSerial(54, 3);
SoftwareSerial LeftSholderSerial = SoftwareSerial(55, 3);
SoftwareSerial RightElbowSerial = SoftwareSerial(56, 3);
SoftwareSerial RightSholderSerial = SoftwareSerial(57, 3);
 

void exitSafeStart()
{
  HeadSerial.write(0x83);
  LeftElbowSerial.write(0x83);
  LeftSholderSerial.write(0x83);
  RightElbowSerial.write(0x83);
  RightSholderSerial.write(0x83);
}

void Head(int speed){
  if (speed < 0)
  {
    HeadSerial.write(0x86);  // motor reverse command
    speed = -speed;  // make speed positive
  }
  else
  {
    HeadSerial.write(0x85);  // motor forward command
  }
  HeadSerial.write(speed & 0x1F);
  HeadSerial.write(speed >> 5);
}

void LeftElbow(int speed){
  if (speed < 0)
  {
    LeftElbowSerial.write(0x86);  // motor reverse command
    speed = -speed;  // make speed positive
  }
  else
  {
    LeftElbowSerial.write(0x85);  // motor forward command
  }
  LeftElbowSerial.write(speed & 0x1F);
  LeftElbowSerial.write(speed >> 5);  
}

void LeftSholder(int speed){
  if (speed < 0)
  {
    LeftSholderSerial.write(0x86);  // motor reverse command
    speed = -speed;  // make speed positive
  }
  else
  {
    LeftSholderSerial.write(0x85);  // motor forward command
  }
  LeftSholderSerial.write(speed & 0x1F);
  LeftSholderSerial.write(speed >> 5);  
}

void RightElbow(int speed){
  if (speed < 0)
  {
    RightElbowSerial.write(0x86);  // motor reverse command
    speed = -speed;  // make speed positive
  }
  else
  {
    RightElbowSerial.write(0x85);  // motor forward command
  }
  RightElbowSerial.write(speed & 0x1F);
  RightElbowSerial.write(speed >> 5);
  
}

void RightSholder(int speed){
  if (speed < 0)
  {
    RightSholderSerial.write(0x86);  // motor reverse command
    speed = -speed;  // make speed positive
  }
  else
  {
    RightSholderSerial.write(0x85);  // motor forward command
  }
  RightSholderSerial.write(speed & 0x1F);
  RightSholderSerial.write(speed >> 5);  
}

 
void setup()
{
  // initialize software serial object with baud rate of 19.2 kbps
  HeadSerial.begin(19200);
  LeftElbowSerial.begin(19200);
  LeftSholderSerial.begin(19200);
  RightElbowSerial.begin(19200);
  RightSholderSerial.begin(19200);
 
  // the Simple Motor Controller must be running for at least 1 ms
  // before we try to send serial data, so we delay here for 5 ms
  delay(5);
 
  // if the Simple Motor Controller has automatic baud detection
  // enabled, we first need to send it the byte 0xAA (170 in decimal)
  // so that it can learn the baud rate
  HeadSerial.write(0xAA);  // send baud-indicator byte
  LeftElbowSerial.write(0xAA)
  LeftSholderSerial.write(0xAA);
  RightElbowSerial.write(0xAA);
  RightSholderSerial.write(0xAA);
 
  // next we need to send the Exit Safe Start command, which
  // clears the safe-start violation and lets the motor run
  exitSafeStart();  // clear the safe-start violation and let the motor run
}
 
void loop()
{
  // full-speed forward is 3200
  // full-speed reverse is -3200
}

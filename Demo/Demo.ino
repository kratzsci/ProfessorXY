#include <SoftwareSerial.h>
#define rxPin 3
#define txPin 42
//Head is 42
//Right Sholder is 40
SoftwareSerial HeadSerial = SoftwareSerial(3, 42);
SoftwareSerial RightSholderSerial = SoftwareSerial(3, 36);
SoftwareSerial RightElbowSerial = SoftwareSerial(3, 32);
SoftwareSerial LeftSholderSerial = SoftwareSerial(3, 24);
SoftwareSerial LeftElbowSerial = SoftwareSerial(3, 22);
 

void exitSafeStart()
{
  HeadSerial.write(0x83);
  RightSholderSerial.write(0x83);
  RightElbowSerial.write(0x83);
  LeftSholderSerial.write(0x83);
  LeftElbowSerial.write(0x83);
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


void setup()
{
  // initialize software serial object with baud rate of 19.2 kbps
  HeadSerial.begin(19200);
  RightSholderSerial.begin(19200);
  RightElbowSerial.begin(19200);
  LeftSholderSerial.begin(19200);
  LeftElbowSerial.begin(19200);
  Serial.begin(9600);
  randomSeed(analogRead(0));
 
  // the Simple Motor Controller must be running for at least 1 ms
  // before we try to send serial data, so we delay here for 5 ms
  delay(5);
 
  // if the Simple Motor Controller has automatic baud detection
  // enabled, we first need to send it the byte 0xAA (170 in decimal)
  // so that it can learn the baud rate
  HeadSerial.write(0xAA);  // send baud-indicator byte
  RightSholderSerial.write(0xAA);  // send baud-indicator byte
  RightElbowSerial.write(0xAA);  // send baud-indicator byte
  LeftSholderSerial.write(0xAA);  // send baud-indicator byte
  LeftElbowSerial.write(0xAA);  // send baud-indicator byte
  

 
  // next we need to send the Exit Safe Start command, which
  // clears the safe-start violation and lets the motor run
  exitSafeStart();  // clear the safe-start violation and let the motor run
}
 
void loop()
{
  //Elbow - negative extends actuator
  //Sholder - negative extend actuator
  int motor = random(0,8);
  int timer = random (1000, 2000);
  
  Serial.print("Motor: ");
  Serial.print(motor);
  Serial.println();
  Serial.print("Timer: ");
  Serial.print(timer);
  Serial.println();
  
  switch(motor){
    case 0:
      Head(3200);
      delay(timer);
      Head(-3200);
      delay(timer);
    break;
    case 1:
      LeftSholder(3200);
      delay(timer);
      LeftSholder(-3200);
      delay(timer);
    break;
    case 2:
      RightSholder(3200);
      delay(timer);
      RightSholder(-3200);
      delay(timer);
    break;
    case 3:
      LeftElbow(3200);
      delay(timer);
      LeftElbow(-3200);
      delay(timer);
    break;
    case 4:
      RightElbow(3200);
      delay(timer);
      RightElbow(-3200);
      delay(timer);
    break;
    case 5:
      Head(3200);
      RightSholder(3200);
      delay(timer);
      Head(-3200);
      RightSholder(-3200);
      delay(timer);
    break;
    case 6:
      RightSholder(3200);
      LeftElbow(3200);
      delay(timer);
      RightSholder(-3200);
      LeftElbow(-3200);
    break;
    case 7:
      Head(3200);
      LeftSholder(3200);
      delay(timer);
      Head(-3200);
      LeftSholder(-3200);
      delay(timer);
    break;
  }
}

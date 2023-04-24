#include <SoftwareSerial.h>
#include <SPI.h>
#include <PS3BT.h>                                                    //Include the necessary libraries.
#include <Servo.h>
#include <SoftwareSerial.h>
#include "RoboClaw.h"

char received;

SoftwareSerial HeadSerial = SoftwareSerial(3, 7);
SoftwareSerial RightSholderSerial = SoftwareSerial(3, 7);
SoftwareSerial RightElbowSerial = SoftwareSerial(3, 7);
SoftwareSerial LeftSholderSerial = SoftwareSerial(3, 7);
SoftwareSerial LeftElbowSerial = SoftwareSerial(3, 7);
SoftwareSerial NeckSerial = SoftwareSerial(3, 7);
//S1 -- D3
//S2 -- D4
SoftwareSerial serial(3, 4);
RoboClaw roboclaw(&serial, 10000);
#define address 0x80

int HeadDirection = 0;
int RightSholderDirection = 0;
int RightElbowDirection = 0;
int LeftSholderDirection = 0;
int LeftElbowDirection = 0;
int NeckDirection = 0;
int DrivingDirection = 5;

void exitSafeStart()
{
  HeadSerial.write(0x83);
  RightSholderSerial.write(0x83);
  RightElbowSerial.write(0x83);
  LeftSholderSerial.write(0x83);
  LeftElbowSerial.write(0x83);
  NeckSerial.write(0x83);
}

void Head(int speed) {
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

void Neck(int speed) {
  if (speed < 0)
  {
    NeckSerial.write(0x86);  // motor reverse command
    speed = -speed;  // make speed positive
  }
  else
  {
    NeckSerial.write(0x85);  // motor forward command
  }
  NeckSerial.write(speed & 0x1F);
  NeckSerial.write(speed >> 5);
}

void RightSholder(int speed) {
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

void RightElbow(int speed) {
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


void LeftSholder(int speed) {
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

void LeftElbow(int speed) {
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

void Driving(int speed) {
  switch (speed) {
    case 1:
      //Forward
      roboclaw.ForwardM1(address, 64);
      roboclaw.ForwardM2(address, 64);
      break;
    case 2:
      //Backward
      roboclaw.BackwardM1(address, 64);
      roboclaw.BackwardM2(address, 64);
      break;
    case 3:
      //Left
      roboclaw.ForwardM1(address, 0);
      roboclaw.ForwardM2(address, 64);
      break;
    case 4:
      //Right
      roboclaw.ForwardM1(address, 64);
      roboclaw.ForwardM2(address, 0);
      break;
    case 5:
      //Forward Right
      roboclaw.ForwardM1(address, 64);
      roboclaw.ForwardM2(address, 32);
      break;
    case 6:
      //Forward Left
      roboclaw.ForwardM1(address, 32);
      roboclaw.ForwardM2(address, 64);
      break;
    case 7:
      //Backward Right
      roboclaw.BackwardM1(address, 32);
      roboclaw.BackwardM2(address, 64);
      break;
    case 8:
      //Backward Left
      roboclaw.BackwardM1(address, 64);
      roboclaw.BackwardM2(address, 32);
      break;
  }
}

void setup() {
  Serial.begin(9600);
  roboclaw.begin(38400);

  // initialize software serial object with baud rate of 19.2 kbps
  HeadSerial.begin(19200);
  RightSholderSerial.begin(19200);
  RightElbowSerial.begin(19200);
  LeftSholderSerial.begin(19200);
  LeftElbowSerial.begin(19200);

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

// Arduino Uno code to receive the message
void loop() {
  if (Serial.available() > 0) {
    received = Serial.read();
  }

  switch (received) {
    case 'T':
      //Right Elbow = 3200
      RightElbow(3200);
      Serial.println("T");
      break;
    case 'X':
      //Right Elbow = -3200
      RightElbow(-3200);
      Serial.println("X");
      break;
    case 'S':
      //Right Sholder = 3200
      RightSholder(3200);
      Serial.println("S");
      break;
    case 'C':
      //Right Sholder = -3200
      RightSholder(-3200);
      Serial.println("C");
      break;
    case 'L':
      //Left Shodler = 3200
      LeftSholder(3200);
      Serial.println("L");
      break;
    case 'R':
      //Left Sholder = -3200
      LeftSholder(-3200);
      Serial.println("R");
      break;
    case 'U':
      //Left Elbow = 3200
      LeftElbow(3200);
      Serial.println("U");
      break;
    case 'D':
      //Left Elbow = -3200
      LeftElbow(-3200);
      Serial.println("D");
      break;
    case '1':
      //Forward
      Driving(1);
      Serial.println("Forward");
      break;
    case '2':
      //Backward
      Driving(2);
      Serial.println("Backward");
      break;
    case '3':
      //Left
      Driving(3);
      Serial.println("Left");
      break;
    case '4':
      //Right
      Driving(4);
      Serial.println("Right");
      break;
    case '5':
      //Forward Right
      Driving(5);
      Serial.println("Forward Right");
      break;
    case '6':
      //Forward Left
      Driving(6);
      Serial.println("Forward Left");
      break;
    case '7':
      //Backward Right
      Driving(7);
      Serial.println("Backward Right");
      break;
    case '8':
      //Backward Left
      Driving(8);
      Serial.println("Backward Left");
      break;
    case 'A':
      //Head Up
      Serial.println("Head Up");
      break;
    case 'B':
      //Head Down
      Serial.println("Head Down");
      break;
    case 'E':
      //Neck Left
      Serial.println("Neck Left");
      break;
    case 'F':
      //Neck Right
      Serial.println("Neck Right");
      break;
  }
}

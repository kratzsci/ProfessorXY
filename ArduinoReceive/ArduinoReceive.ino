#include <SoftwareSerial.h>
#include <SPI.h>
// #include <PS3BT.h>                                                    //Include the necessary libraries.
// #include <Servo.h>
#include <SoftwareSerial.h>
#include "RoboClaw.h"

SoftwareSerial HeadSerial = SoftwareSerial(3, 9);
SoftwareSerial RightShoulderSerial = SoftwareSerial(3, 7);
SoftwareSerial RightElbowSerial = SoftwareSerial(3, 8);
SoftwareSerial LeftShoulderSerial = SoftwareSerial(3, 27);
SoftwareSerial LeftElbowSerial = SoftwareSerial(3, 28);
SoftwareSerial NeckSerial = SoftwareSerial(3, 29);

SoftwareSerial serial(10, 11);
RoboClaw roboclaw(&serial, 10000);
#define address 0x80
int timer = 500;


void exitSafeStart()
{
  HeadSerial.write(0x83);
  RightShoulderSerial.write(0x83);
  RightElbowSerial.write(0x83);
  LeftShoulderSerial.write(0x83);
  LeftElbowSerial.write(0x83);
  NeckSerial.write(0x83);
}

void control(char command){
//  Serial.println("Limb control.");
  int speed = 3200;
  int forward = 0x85;
  int reverse = 0x86;
    //  Serial.println("Simple Driving");
  int speedD = 64;   // 0-127
  int Turn = 127;
  int Stop = 0;
  // Head up
  if (command == 'U') {
    Serial.println("Head up");
    HeadSerial.write(forward);          // motor command
    HeadSerial.write(speed & 0x1F);     // Send the low-order 5 bits of the speed value
    HeadSerial.write(speed >> 5);       // Shift the speed value 5 bits to the right and send the resulting value
  }
  // Head down
  else if (command == 'D') {
    Serial.println("Head down");
    HeadSerial.write(reverse);          // motor command
    HeadSerial.write(speed & 0x1F);     // Send the low-order 5 bits of the speed value
    HeadSerial.write(speed >> 5);       // Shift the speed value 5 bits to the right and send the resulting value
  }

  // Neck left
  else if (command == 'L') {
    Serial.println("Neck left");
    NeckSerial.write(reverse);          // motor command
    NeckSerial.write(speed & 0x1F);
    NeckSerial.write(speed >> 5);
  }
  // Neck right
  else if (command == 'R') {
    Serial.println("Neck right");
    NeckSerial.write(forward);          // motor command
    NeckSerial.write(speed & 0x1F);
    NeckSerial.write(speed >> 5);
  }

  // Left elbow up
  else if (command == 'T') {
    Serial.println("Left Elbow up");
    LeftElbowSerial.write(forward);       // motor command
    LeftElbowSerial.write(speed & 0x1F);
    LeftElbowSerial.write(speed >> 5);
  }
  // Left elbow down
  else if (command == 'C') {
    Serial.println("Left Elbow down");
    LeftElbowSerial.write(reverse);       // motor command
    LeftElbowSerial.write(speed & 0x1F);
    LeftElbowSerial.write(speed >> 5);
  }

  // Right elbow up
  else if (command == 'S') {
    Serial.println("Right Elbow up");
    RightElbowSerial.write(forward);       // motor command
    RightElbowSerial.write(speed & 0x1F);
    RightElbowSerial.write(speed >> 5);
  }
  // Right elbow down
  else  if (command == 'X') {
    Serial.println("Right Elbow down");
    RightElbowSerial.write(reverse);       // motor command
    RightElbowSerial.write(speed & 0x1F);
    RightElbowSerial.write(speed >> 5);
  }

  // Left shoulder up
  else if (command == 'E') {
    Serial.println("Left Shoulder up");
    LeftShoulderSerial.write(forward);     // motor command
    LeftShoulderSerial.write(speed & 0x1F);
    LeftShoulderSerial.write(speed >> 5);
  }
  // Left shoulder down
  else if (command == 'F') {
    Serial.println("Left Shoulder down");
    LeftShoulderSerial.write(reverse);     // motor command
    LeftShoulderSerial.write(speed & 0x1F);
    LeftShoulderSerial.write(speed >> 5);
  }

  // Right shoulder up
  else if (command == 'G') {
    Serial.println("Right Shoulder up");
    RightShoulderSerial.write(forward);     // motor command
    RightShoulderSerial.write(speed & 0x1F);
    RightShoulderSerial.write(speed >> 5);
  }
  // Right shoulder down
  else if (command == 'H') {
    Serial.println("Right Shoulder down");
    RightShoulderSerial.write(reverse);     // motor command
    RightShoulderSerial.write(speed & 0x1F);
    RightShoulderSerial.write(speed >> 5);
  }
  // Drive the robot with the directional pad
  else if (command == '2') {
    Serial.println("Drive Backward");
    roboclaw.BackwardM1(address, speedD);
    roboclaw.BackwardM2(address, speedD);
  }
  else if (command == '1') {
    Serial.println("Drive Forward");
    roboclaw.ForwardM1(address, speedD);
    roboclaw.ForwardM2(address, speedD);
  }
  else if (command == '4') {
    Serial.println("Turn Left");
    roboclaw.ForwardM1(address, Turn);
    roboclaw.ForwardM2(address, Stop);
  }
  else if (command == '3') {
    Serial.println("Turn Right");
    roboclaw.ForwardM1(address, Stop);
    roboclaw.ForwardM2(address, Turn);
  }
  else if (command == '0'){
    Serial.println("Stop");
    roboclaw.ForwardM1(address, Stop);
    roboclaw.ForwardM2(address, Stop);
    
    LeftShoulderSerial.write(forward);     // motor command
    LeftShoulderSerial.write(Stop & 0x1F);
    LeftShoulderSerial.write(Stop >> 5);

    RightShoulderSerial.write(forward);     // motor command
    RightShoulderSerial.write(Stop & 0x1F);
    RightShoulderSerial.write(Stop >> 5);

    LeftElbowSerial.write(forward);     // motor command
    LeftElbowSerial.write(Stop & 0x1F);
    LeftElbowSerial.write(Stop >> 5);

    RightElbowSerial.write(forward);     // motor command
    RightElbowSerial.write(Stop & 0x1F);
    RightElbowSerial.write(Stop >> 5);

    HeadSerial.write(forward);     // motor command
    HeadSerial.write(Stop & 0x1F);
    HeadSerial.write(Stop >> 5);
  }
}

void setup() {
  Serial.begin(9600);
  roboclaw.begin(38400);

  // initialize software serial object with baud rate of 19.2 kbps
  HeadSerial.begin(19200);
  RightShoulderSerial.begin(19200);
  RightElbowSerial.begin(19200);  
  LeftShoulderSerial.begin(19200);
  LeftElbowSerial.begin(19200);

  // the Simple Motor Controller must be running for at least 1 ms
  // before we try to send serial data, so we delay here for 5 ms
  delay(5);

  // if the Simple Motor Controller has automatic baud detection
  // enabled, we first need to send it the byte 0xAA (170 in decimal)
  // so that it can learn the baud rate
  HeadSerial.write(0xAA);           // send baud-indicator byte
  RightShoulderSerial.write(0xAA);   // send baud-indicator byte
  RightElbowSerial.write(0xAA);     // send baud-indicator byte
  LeftShoulderSerial.write(0xAA);    // send baud-indicator byte
  LeftElbowSerial.write(0xAA);      // send baud-indicator byte

  // next we need to send the Exit Safe Start command, which
  // clears the safe-start violation and lets the motor run
  exitSafeStart();      // clear the safe-start violation and let the motor run
}

// Arduino code to receive the message
void loop() {
  char command;
  int mode;
  command = ' ';
  //Serial reading
  if (Serial.available() > 0) {
    command = Serial.read();
  }
  control(command);
  delay(5);
}

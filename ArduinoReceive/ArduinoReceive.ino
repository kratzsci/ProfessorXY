#include <SoftwareSerial.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include "RoboClaw.h"

SoftwareSerial HeadSerial = SoftwareSerial(3, 9);
SoftwareSerial RightShoulderSerial = SoftwareSerial(3, 7);
SoftwareSerial RightElbowSerial = SoftwareSerial(3, 8);
SoftwareSerial LeftShoulderSerial = SoftwareSerial(3, 27);
SoftwareSerial LeftElbowSerial = SoftwareSerial(3, 28);
SoftwareSerial NeckSerial = SoftwareSerial(3, 29);
//S1 -- D3
//S2 -- D4
SoftwareSerial serial(10, 11);
RoboClaw roboclaw(&serial, 10000);
#define address 0x80

void exitSafeStart()
{
  HeadSerial.write(0x83);
  RightShoulderSerial.write(0x83);
  RightElbowSerial.write(0x83);
  LeftShoulderSerial.write(0x83);
  LeftElbowSerial.write(0x83);
  NeckSerial.write(0x83);
}

// Head
void headUp(int speed) {
  Serial.println("Head up");
  HeadSerial.write(0x85);           // motor command
  HeadSerial.write(speed & 0x1F);   // Send the low-order 5 bits of the speed value
  HeadSerial.write(speed >> 5);     // Shift the speed value 5 bits to the right and send the resulting value
}
void headDown(int speed) {
  Serial.println("Head down");
  HeadSerial.write(0x86);           // motor command
  HeadSerial.write(speed & 0x1F);   // Send the low-order 5 bits of the speed value
  HeadSerial.write(speed >> 5);     // Shift the speed value 5 bits to the right and send the resulting value
}

// Neck
void neckUp(int speed) {
  Serial.println("Neck left");
  NeckSerial.write(0x86);
  NeckSerial.write(speed & 0x1F);
  NeckSerial.write(speed >> 5);
}
void neckDown(int speed) {
  Serial.println("Neck right");
  NeckSerial.write(0x85);
  NeckSerial.write(speed & 0x1F);
  NeckSerial.write(speed >> 5);
}

// Left elbow
void leftElbowUp(int speed) {
  Serial.println("Left Elbow up");
  LeftElbowSerial.write(0x85);
  LeftElbowSerial.write(speed & 0x1F);
  LeftElbowSerial.write(speed >> 5);
}
void leftElbowDown(int speed) {
  Serial.println("Left Elbow down");
  LeftElbowSerial.write(0x86);
  LeftElbowSerial.write(speed & 0x1F);
  LeftElbowSerial.write(speed >> 5);
}

// Right elbow
void rightElbowUp(int speed) {
    Serial.println("Right Elbow up");
    RightElbowSerial.write(0x85);
    RightElbowSerial.write(speed & 0x1F);
    RightElbowSerial.write(speed >> 5);
}
void rightElbowDown(int speed) {
    Serial.println("Right Elbow down");
    RightElbowSerial.write(0x86);
    RightElbowSerial.write(speed & 0x1F);
    RightElbowSerial.write(speed >> 5);
}

// Left shoulder
void leftShoulderUp(int speed) {
  Serial.println("Left Shoulder up");
  LeftShoulderSerial.write(0x85);
  LeftShoulderSerial.write(speed & 0x1F);
  LeftShoulderSerial.write(speed >> 5);
}
void leftShoulderDown(int speed) {
  Serial.println("Left Shoulder down");
  LeftShoulderSerial.write(0x86);
  LeftShoulderSerial.write(speed & 0x1F);
  LeftShoulderSerial.write(speed >> 5);
}

// Right Shoulder
void rightShoulderUp(int speed) {
  Serial.println("Right Shoulder up");
  RightShoulderSerial.write(0x85);
  RightShoulderSerial.write(speed & 0x1F);
  RightShoulderSerial.write(speed >> 5);
}
void rightShoulderDown(int speed) {
  Serial.println("Right Shoulder down");
  RightShoulderSerial.write(0x86);
  RightShoulderSerial.write(speed & 0x1F);
  RightShoulderSerial.write(speed >> 5);
}

void Demo(void) {
  Serial.println("Demo mode.");
  int motor = random(0, 8);
  int timer = (random(100, 200));
  int speed = 3200;

  switch (motor) {
    case 0:
      headUp(speed);
      delay(timer);

      headDown(speed);
      delay(timer);
      break;

    case 1:
      leftShoulderUp(speed);
      delay(timer);

      leftShoulderDown(speed);
      delay(timer);
      break;

    case 2:
      rightShoulderUp(speed);
      delay(timer);

      rightShoulderDown(speed);
      delay(timer);
      break;

    case 3:
      leftElbowUp(speed);
      delay(timer);

      leftElbowDown(speed);
      delay(timer);
      break;

    case 4:
      rightElbowUp(speed);
      delay(timer);

      rightElbowDown(speed);
      delay(timer);
      break;

    case 5:
      headUp(speed);
      rightShoulderUp(speed);
      delay(timer);

      headDown(speed);
      rightShoulderDown(speed);
      delay(timer);
      break;

    case 6:
      rightShoulderUp(speed);
      leftElbowUp(speed);
      delay(timer);

      rightShoulderDown(speed);
      leftElbowDown(speed);
      delay(timer);
      break;

    case 7:
      headUp(speed);
      leftShoulderUp(speed);
      delay(timer);

      headDown(speed);
      leftShoulderDown(speed);
      delay(timer);
      break;

    default:
      Serial.println("Demo: No movement case.");
      break;
  }
}

void fullStop(void) {
  roboclaw.ForwardM1(address, 0);
  roboclaw.ForwardM2(address, 0);
  headUp(0);
  headDown(0);
  neckUp(0);
  neckDown(0);
  leftElbowUp(0);
  leftElbowDown(0);
  rightElbowUp(0);
  rightElbowDown(0);
  leftShoulderUp(0);
  leftShoulderDown(0);
  rightShoulderUp(0);
  rightShoulderDown(0);
}

void robotControl(char command) {
  Serial.println("Robot Control.");
  int speedL = 3200;
  int stop = 0;
  int forward = 0x85;
  int reverse = 0x86;
  
  int speedD = 64;   // 0-127
  int Turn = 127;
  int Stop = 0;

  // Full stop: No button pressed or Manual button pressed
//  if (command == '9' || command == 'Y') {
//    fullStop();
//  }

  // Stop driving the robot
  if (command == '0') {
    Serial.println("Stop Driving");
    roboclaw.ForwardM1(address, Stop);
    roboclaw.ForwardM2(address, Stop);
  }

  // Drive the robot with the analog sticks
  else if (command == '1') {
    Serial.println("Drive Forward");
    roboclaw.ForwardM1(address, speedD);
    roboclaw.ForwardM2(address, speedD);
  }
  else if (command == '2') {
    Serial.println("Drive Backward");
    roboclaw.BackwardM1(address, speedD);
    roboclaw.BackwardM2(address, speedD);
  }
  else if (command == '3') {
    Serial.println("Turn Right");
    roboclaw.BackwardM1(address, Stop);
    roboclaw.ForwardM2(address, Turn);
  }
  else if (command == '4') {
    Serial.println("Turn Left");
    roboclaw.ForwardM1(address, Stop);
    roboclaw.BackwardM2(address, Turn);
  }

  // Head
  else if (command == '5') {
    headUp(speedL);
  }
  else if (command == '6') {
    headDown(speedL);
  }

  // Neck
  else if (command == '7') {
    neckUp(speedL);
  }
  else if (command == '8') {
    neckDown(speedL);
  }

  // Stop moving the Head/Neck
  else if (command == 'I') {
    headUp(stop);
    neckUp(stop);
  }

  // Left elbow
  else if (command == 'U') {
    leftElbowUp(speedL);
  }
  else if (command == 'D') {
    leftElbowDown(speedL);
  }
  // Left elbow stop
  else if (command == 'R') {
    leftElbowUp(stop);
  }

  // Right elbow
  else if (command == 'T') {
    rightElbowUp(speedL);
  }
  else if (command == 'X') {
    rightElbowDown(speedL);
  }
  // Right elbow stop
  else if (command == 'C') {
    rightElbowUp(stop);
  }

  // Left shoulder
  else if (command == 'E') {
    leftShoulderUp(speedL);
  }
  else if (command == 'F') {
    leftShoulderDown(speedL);
  }
  // Left shoulder stop
  else if (command == 'L') {
    leftShoulderUp(stop);
  }

  // Right shoulder
  else if (command == 'G') {
    rightShoulderUp(speedL);
  }
  else if (command == 'H') {
    rightShoulderDown(speedL);
  }
  // Right shoulder stop
  else if (command == 'S') {
    rightShoulderUp(stop);
  }
}

// TODO: fix this
int modeControl(char command, int mode){
  Serial.println("Mode Control.");

  if (command == 'A') {
    mode = 0;             // Start button
  }
  if (command == 'B') {
    mode = 1;             // Select button
  }
  if (command == 'Z') {
    mode = 2;             // PS button
  }
  return mode;
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

  //Serial reading
  if (Serial.available() > 0) {
    command = Serial.read();
    Serial.println(command);

    // Controls the mode of the robot
    // mode = modeControl(command, mode);


    robotControl(command);
  
    // Demo();
  
    command = ' ';
  }
  delay(5);
}

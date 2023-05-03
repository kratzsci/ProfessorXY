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
//S1 -- D3
//S2 -- D4
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

void Head(int speed) {
  if (speed < 0)
  {
    Serial.println("Head Down");
    HeadSerial.write(0x86);             // motor reverse command
    speed = -speed;                     // make speed positive
  }
  else
  {
    Serial.println("Head up");
    HeadSerial.write(0x85);             // motor forward command
  }
  HeadSerial.write(speed & 0x1F);       // Send the low-order 5 bits of the speed value
  HeadSerial.write(speed >> 5);         // Shift the speed value 5 bits to the right and send the resulting value
}

void Neck(int speed) {
  if (speed < 0)
  {
    Serial.println("Neck down");
    NeckSerial.write(0x86);             // motor reverse command
    speed = -speed;                     // make speed positive
  }
  else
  {
    Serial.println("Neck up");
    NeckSerial.write(0x85);             // motor forward command
  }
  NeckSerial.write(speed & 0x1F);
  NeckSerial.write(speed >> 5);
}

void RightShoulder(int speed) {
  if (speed < 0)
  {
    Serial.println("Right Shoulder down");
    RightShoulderSerial.write(0x86);     // motor reverse command
    speed = -speed;                     // make speed positive
  }
  else
  {
    Serial.println("Right Shoulder up");
    RightShoulderSerial.write(0x85);     // motor forward command
  }
  RightShoulderSerial.write(speed & 0x1F);
  RightShoulderSerial.write(speed >> 5);
}

void RightElbow(int speed) {
  if (speed < 0)
  {
    Serial.println("Right Elbow down");
    RightElbowSerial.write(0x86);       // motor reverse command
    speed = -speed;                     // make speed positive
  }
  else
  {
    Serial.println("Right Elbow up");

    RightElbowSerial.write(0x85);       // motor forward command
  }
  RightElbowSerial.write(speed & 0x1F);
  RightElbowSerial.write(speed >> 5);
}

void LeftShoulder(int speed) {
  if (speed < 0)
  {
    Serial.println("Left Shoulder down");
    LeftShoulderSerial.write(0x86);      // motor reverse command
    speed = -speed;                     // make speed positive
  }
  else
  {
    Serial.println("Left Shoulder up");
    LeftShoulderSerial.write(0x85);      // motor forward command
  }

  LeftShoulderSerial.write(speed & 0x1F);
  LeftShoulderSerial.write(speed >> 5);
}

void LeftElbow(int speed) {
  if (speed < 0)
  {
    Serial.println("Left Elbow down");
    LeftElbowSerial.write(0x86);        // motor reverse command
    speed = -speed;                     // make speed positive
  }
  else
  {
    Serial.println("Left Elbow up");
    LeftElbowSerial.write(0x85);        // motor forward command
  }

  LeftElbowSerial.write(speed & 0x1F);
  LeftElbowSerial.write(speed >> 5);
}

void Demo(void) {
  Serial.println("Demo mode.");
  int motor = random(0, 8);
  int timer = (random(100, 200));

  switch (motor) {
    case 0:
      Head(3200);
      delay(timer);
      Head(-3200);
      delay(timer);
      break;

    case 1:
      LeftShoulder(3200);
      delay(timer);
      LeftShoulder(-3200);
      delay(timer);
      break;

    case 2:
      RightShoulder(3200);
      delay(timer);
      RightShoulder(-3200);
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
      RightShoulder(3200);
      delay(timer);
      Head(-3200);
      RightShoulder(-3200);
      delay(timer);
      break;

    case 6:
      RightShoulder(3200);
      LeftElbow(3200);
      delay(timer);
      RightShoulder(-3200);
      LeftElbow(-3200);
      delay(timer);
      break;

    case 7:
      Head(3200);
      LeftShoulder(3200);
      delay(timer);
      Head(-3200);
      LeftShoulder(-3200);
      delay(timer);
      break;

    default:
      Serial.println("Demo: No movement case.");
      break;
  }
}

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

void robotControl(char command){
  Serial.println("Robot Control.");
  int speedL = 3200;
  int stop = 0;
  int forward = 0x85;
  int reverse = 0x86;
  
  int speedD = 64;   // 0-127
  int Turn = 127;
  int Stop = 0;

  // Drive the robot with the directional pad
  if (command == '0') {
    Serial.println("Stop Driving");
    roboclaw.ForwardM1(address, Stop);
    roboclaw.ForwardM2(address, Stop);
  }
  else if (command == '1') {
    Serial.println("Drive Forward");
    roboclaw.ForwardM1(address, speedD);
    roboclaw.ForwardM2(address, speedD);
  }
  else if (command == '4') {
    Serial.println("Turn Left");
    roboclaw.ForwardM1(address, Stop);
    roboclaw.BackwardM2(address, Turn);
  }
  else if (command == '3') {
    Serial.println("Turn Right");
    roboclaw.BackwardM1(address, Stop);
    roboclaw.ForwardM2(address, Turn);
  }
  else if (command == '2') {
    Serial.println("Drive Backward");
    roboclaw.BackwardM1(address, speedD);
    roboclaw.BackwardM2(address, speedD);
  }
  
  // Head up
  else if (command == 'U') {
    Serial.println("Head up");
    HeadSerial.write(forward);          // motor command
    HeadSerial.write(speedL & 0x1F);     // Send the low-order 5 bits of the speed value
    HeadSerial.write(speedL >> 5);       // Shift the speed value 5 bits to the right and send the resulting value
  }
  // Head down
  else if (command == 'D') {
    Serial.println("Head down");
    HeadSerial.write(reverse);          // motor command
    HeadSerial.write(speedL & 0x1F);     // Send the low-order 5 bits of the speed value
    HeadSerial.write(speedL >> 5);       // Shift the speed value 5 bits to the right and send the resulting value
  }

  // Neck left
  else if (command == 'L') {
    Serial.println("Neck left");
    NeckSerial.write(reverse);          // motor command
    NeckSerial.write(speedL & 0x1F);
    NeckSerial.write(speedL >> 5);
  }
  // Neck right
  else if (command == 'R') {
    Serial.println("Neck right");
    NeckSerial.write(forward);          // motor command
    NeckSerial.write(speedL & 0x1F);
    NeckSerial.write(speedL >> 5);
  }

  // Left elbow up
  else if (command == 'T') {
    Serial.println("Left Elbow up");
    LeftElbowSerial.write(forward);       // motor command
    LeftElbowSerial.write(speedL & 0x1F);
    LeftElbowSerial.write(speedL >> 5);
  }
  // Left elbow down
  else if (command == 'C') {
    Serial.println("Left Elbow down");
    LeftElbowSerial.write(reverse);       // motor command
    LeftElbowSerial.write(speedL & 0x1F);
    LeftElbowSerial.write(speedL >> 5);
  }

  // Right elbow up
  else if (command == 'S') {
    Serial.println("Right Elbow up");
    RightElbowSerial.write(forward);       // motor command
    RightElbowSerial.write(speedL & 0x1F);
    RightElbowSerial.write(speedL >> 5);
  }
  // Right elbow down
  else if (command == 'X') {
    Serial.println("Right Elbow down");
    RightElbowSerial.write(reverse);       // motor command
    RightElbowSerial.write(speedL & 0x1F);
    RightElbowSerial.write(speedL >> 5);
  }

  // Left shoulder up
  else if (command == 'E') {
    Serial.println("Left Shoulder up");
    LeftShoulderSerial.write(forward);     // motor command
    LeftShoulderSerial.write(speedL & 0x1F);
    LeftShoulderSerial.write(speedL >> 5);
  }
  // Left shoulder down
  else if (command == 'F') {
    Serial.println("Left Shoulder down");
    LeftShoulderSerial.write(reverse);     // motor command
    LeftShoulderSerial.write(speedL & 0x1F);
    LeftShoulderSerial.write(speedL >> 5);
  }

  // Right shoulder up
  else if (command == 'G') {
    Serial.println("Right Shoulder up");
    RightShoulderSerial.write(forward);     // motor command
    RightShoulderSerial.write(speedL & 0x1F);
    RightShoulderSerial.write(speedL >> 5);
  }
  // Right shoulder down
  else if (command == 'H') {
    Serial.println("Right Shoulder down");
    RightShoulderSerial.write(reverse);     // motor command
    RightShoulderSerial.write(speedL & 0x1F);
    RightShoulderSerial.write(speedL >> 5);
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

  //Serial reading
  if (Serial.available() > 0) {
    command = Serial.read();
    Serial.println(command);
    robotControl(command);
    
    // simpleDrive(command);
    // Limb(command);
    // Demo();
  
    command = ' ';
  }
  delay(5);
  // Controls the mode of the robot
  // mode = modeControl(command, mode);
  
  // Limb move mode - Share button
  // Move the arms and head
// if (mode == 0) {
//   Limb(command);
// }
 // Simple drive mode - Options button
 // Driving with the directional pad
// if (mode == 1) {
//   simpleDrive(command);
// }
//  // Demo mode - PS button
//  // Randomly moves arms for demonstration
//  if (mode == 2) {
//    Demo();
//  }
}

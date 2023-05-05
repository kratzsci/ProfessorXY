#include <SoftwareSerial.h>
#include <SPI.h>
<<<<<<< HEAD
#include <PS3BT.h>                                                    //Include the necessary libraries.
=======
// #include <PS3BT.h>                                                    //Include the necessary libraries.
>>>>>>> main
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
<<<<<<< HEAD
int timer = 100;      // 100ms
int mode = 0;         // default to ps control mode
=======
int timer = 500;
>>>>>>> main


void exitSafeStart()
{
  HeadSerial.write(0x83);
  RightShoulderSerial.write(0x83);
  RightElbowSerial.write(0x83);
  LeftShoulderSerial.write(0x83);
  LeftElbowSerial.write(0x83);
  NeckSerial.write(0x83);
}

<<<<<<< HEAD
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
  delay(timer);
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
  delay(timer);
}

void RightSholder(int speed) {
  if (speed < 0)
  {
    Serial.println("Right Sholder down");
    RightSholderSerial.write(0x86);     // motor reverse command
    speed = -speed;                     // make speed positive
  }
  else
  {
    Serial.println("Right Sholder up");
    RightSholderSerial.write(0x85);     // motor forward command
  }
  RightSholderSerial.write(speed & 0x1F);
  RightSholderSerial.write(speed >> 5);
  delay(timer);
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
  delay(timer);
}

void LeftSholder(int speed) {
  if (speed < 0)
  {
    Serial.println("Left Sholder down");
    LeftSholderSerial.write(0x86);      // motor reverse command
    speed = -speed;                     // make speed positive
  }
  else
  {
    Serial.println("Left Sholder up");
    LeftSholderSerial.write(0x85);      // motor forward command
  }

  LeftSholderSerial.write(speed & 0x1F);
  LeftSholderSerial.write(speed >> 5);
  delay(timer);
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
  delay(timer);
}

void Driving(int speed) {
  switch (speed) {
    case 0:
      //Stop
      Serial.println("Stop Driving");
      roboclaw.ForwardM1(address, 0);
      roboclaw.ForwardM2(address, 0);
      break;
    case 1:
      //Backward
      Serial.println("Drive backward");
      roboclaw.BackwardM1(address, 127);
      roboclaw.BackwardM2(address, 127);
      break;
    case 2:
      //Forward
      Serial.println("Drive forward");
      roboclaw.ForwardM1(address, 127);
      roboclaw.ForwardM2(address, 127);
      break;
    case 3:
      //Left
      Serial.println("Drive left");
      roboclaw.ForwardM1(address, 0);
      roboclaw.ForwardM2(address, 127);
      break;
    case 4:
      //Right
      Serial.println("Drive right");
      roboclaw.ForwardM1(address, 127);
      roboclaw.ForwardM2(address, 0);
      break;
    case 5:
      //Forward Right
      Serial.println("Drive forward right");
      roboclaw.ForwardM1(address, 127);
      roboclaw.ForwardM2(address, 64);
      break;
    case 6:
      //Forward Left
      Serial.println("Drive forward left");
      roboclaw.ForwardM1(address, 64);
      roboclaw.ForwardM2(address, 127);
      break;
    case 7:
      //Backward Right
      Serial.println("Drive backward right");
      roboclaw.BackwardM1(address, 64);
      roboclaw.BackwardM2(address, 127);
      break;
    case 8:
      //Backward Left
      Serial.println("Drive backward left");
      roboclaw.BackwardM1(address, 127);
      roboclaw.BackwardM2(address, 64);
      break;
    default:
      Serial.println("Driving: No drive case.");
      break;
=======
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
>>>>>>> main
  }
  delay(timer);
}

<<<<<<< HEAD
void controller(int received) {
  Serial.println("Remote control mode");
  switch (received) {
    case 'A':               // Start button
      mode = 0;
      delay(100);
      break;
    case 'B':               // Select button
      mode = 1;
      delay(100);
      break;
    case 'E':               // PS button
      mode = 2;
      delay(100);
      break;
    default:
      Serial.println("Demo: Mode error.");
      break;
  }
  
  switch (received) {
    case 'U':               // Head up
      Head(3200);
      Head(0);
      break;
    case 'D':               // Head down
      Head(-3200);
      Head(0);
      break;

    //  case 'L':               // Neck left
    //    Neck(-3200);
    //    Neck(0);
    //    break;
    //  case 'R':               // Neck right
    //    Neck(3200);
    //    Neck(0);
    //    break;

    case 'S':               // Right shoulder up
      RightSholder(3200);
      RightSholder(0);
      break;
    case 'C':               // Right shoulder down
      RightSholder(-3200);
      RightSholder(0);
      break;

    case 'T':               // Right elbow up
      RightElbow(3200);
      RightElbow(0);
      break;
    case 'X':               // Right elbow down
      RightElbow(-3200);
      RightElbow(0);
      break;

    case 'L':               // Left shoulder up
      LeftSholder(3200);
      LeftSholder(0);
      break;
    case 'R':               // Left shoulder up
      LeftSholder(-3200);
      LeftSholder(0);
      break;

    // case 'U':               // Left elbow up
    //   LeftElbow(3200);
    //   LeftElbow(0);
    //   break;
    // case 'D':               // Left elbow down
    //   LeftElbow(-3200);
    //   LeftElbow(0);
    //   break;

    case '1':               // Drive forward
      Driving(1);
      Driving(0);
      break;
    case '2':               // Drive backward
      Driving(2);
      Driving(0);
      break;

    case '3':               // Drive left
      Driving(3);
      Driving(0);
      break;
    case '4':               // Drive right
      Driving(4);
      Driving(0);
      break;

    case '5':               // Drive forward right
      Driving(5);
      Driving(0);
      break;
    case '6':               // Drive forward left
      Driving(6);
      Driving(0);
      break;

    case '7':               // Drive backward right
      Driving(7);
      Driving(0);
      break;
    case '8':               // Drive backward left
      Driving(8);
      Driving(0);
      break;

    default:
      Serial.println("Controller: No movement case.");
      break;
  }
}

void demo(int received) {
  Serial.println("Demo mode.");
  int motor = random(0, 8);
  int timerRan = (random(1000, 2000) - timer);

  switch (received) {
    case 'A':               // Start button
      mode = 0;
      delay(100);
      break;
    case 'B':               // Select button
      mode = 1;
      delay(100);
      break;
    case 'E':               // PS button
      mode = 2;
      delay(100);
      break;
    default:
      Serial.println("Demo: Mode error.");
      break;
  }

  switch (motor) {
    case 0:
      Head(3200);
      delay(timerRan);
      Head(-3200);
      delay(timerRan);
      break;

    case 1:
      LeftSholder(3200);
      delay(timerRan);
      LeftSholder(-3200);
      delay(timerRan);
      break;

    case 2:
      RightSholder(3200);
      delay(timerRan);
      RightSholder(-3200);
      delay(timerRan);
      break;

    case 3:
      LeftElbow(3200);
      delay(timerRan);
      LeftElbow(-3200);
      delay(timerRan);
      break;

    case 4:
      RightElbow(3200);
      delay(timerRan);
      RightElbow(-3200);
      delay(timerRan);
      break;

    case 5:
      Head(3200);
      RightSholder(3200);
      delay(timerRan);
      Head(-3200);
      RightSholder(-3200);
      delay(timerRan);
      break;

    case 6:
      RightSholder(3200);
      LeftElbow(3200);
      delay(timerRan);
      RightSholder(-3200);
      LeftElbow(-3200);
      break;

    case 7:
      Head(3200);
      LeftSholder(3200);
      delay(timerRan);
      Head(-3200);
      LeftSholder(-3200);
      delay(timerRan);
      break;

    default:
      Serial.println("Demo: No movement case.");
      break;
  }
}

void DrivingSimple(int speed) {
  switch (speed) {
    case 0:
      // Stop
      Serial.println("Stop Driving");
      roboclaw.ForwardM1(address, 0);
      roboclaw.ForwardM2(address, 0);
      break;
    case 1:
      // Backward
      Serial.println("Drive backward");
      roboclaw.BackwardM1(address, 127);
      roboclaw.BackwardM2(address, 127);
      break;
    case 2:
      // Forward
      Serial.println("Drive forward");
      roboclaw.ForwardM1(address, 127);
      roboclaw.ForwardM2(address, 127);
      break;
    case 3:
      // Left pivot
      Serial.println("Pivot left");
      roboclaw.ForwardM1(address, 0);
      roboclaw.ForwardM2(address, 127);
      break;
    case 4:
      // Right pivot
      Serial.println("Pivot right");
      roboclaw.ForwardM1(address, 127);
      roboclaw.ForwardM2(address, 0);
      break;
    case 5:
      // Left turn in place
      Serial.println("Left turn in place");
      roboclaw.ForwardM1(address, 64);
      roboclaw.BackwardM2(address, 64);
      break;
    case 6:
      // Right turn in place
      Serial.println("Right turn in place");
      roboclaw.BackwardM1(address, 64);
      roboclaw.ForwardM2(address, 64);
      break;
    default:
      Serial.println("Driving Simple: No drive case.");
      break;
  }
  delay(timer);
=======
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
>>>>>>> main
}

void controllerDrive(int received) {
  Serial.println("Remote control mode: Simple Driving");
  switch (received) {
    case 'A':               // Start button
      mode = 0;
      delay(100);
      break;
    case 'B':               // Select button
      mode = 1;
      delay(100);
      break;
    case 'E':               // PS button
      mode = 2;
      delay(100);
      break;
    default:
      Serial.println("Controller drive: Mode error.");
      break;
  }

  switch (received) {
    case '1':               // Drive forward
      DrivingSimple(1);
      DrivingSimple(0);
      break;
    case '2':               // Drive backward
      DrivingSimple(2);
      DrivingSimple(0);
      break;

    case '3':               // Left pivot
      DrivingSimple(3);
      DrivingSimple(0);
      break;
    case '4':               // Right pivot
      DrivingSimple(4);
      DrivingSimple(0);
      break;

    case '5':               // Left turn in place
      DrivingSimple(5);
      DrivingSimple(0);
      break;
    case '6':               // Right turn in place
      DrivingSimple(6);
      DrivingSimple(0);
      break;

    default:
      Serial.println("Controller drive: No drive case.");
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
  HeadSerial.write(0xAA);           // send baud-indicator byte
  RightSholderSerial.write(0xAA);   // send baud-indicator byte
  RightElbowSerial.write(0xAA);     // send baud-indicator byte
  LeftSholderSerial.write(0xAA);    // send baud-indicator byte
  LeftElbowSerial.write(0xAA);      // send baud-indicator byte

  // next we need to send the Exit Safe Start command, which
  // clears the safe-start violation and lets the motor run
  exitSafeStart();      // clear the safe-start violation and let the motor run
}

// Arduino Uno code to receive the message
void loop() {
  char received = 'p';  // This is null character chosen to represent empty state

  //Serial reading
  while (Serial.available() > 0) {
    received = Serial.read();
  }

  // Mode switching - Controller, Demo, and Contrl drive mode
  // Default is controller mode
  if (mode == 0 && received != 'p') {
    controller(received);
  }
  else if (mode == 1 && received != 'p') {
    demo(received);
  }
  else if (mode == 2 && received != 'p') {
    controllerDrive(received);
  }
  else {
    if (received == 'p') {
      Serial.println("Received null.");
    }
    else {
      Serial.println("Mode Error.");
    }
  }
}
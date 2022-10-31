#include <SoftwareSerial.h>
#include <SPI.h>
#include <PS3BT.h>                                                    //Include the necessary libraries.
#include <Servo.h>
#include <SoftwareSerial.h>
#include "RoboClaw.h"

SoftwareSerial HeadSerial = SoftwareSerial(3, 42);
SoftwareSerial RightSholderSerial = SoftwareSerial(3, 36);
SoftwareSerial RightElbowSerial = SoftwareSerial(3, 32);
SoftwareSerial LeftSholderSerial = SoftwareSerial(3, 24);
SoftwareSerial LeftElbowSerial = SoftwareSerial(3, 22);
SoftwareSerial NeckSerial = SoftwareSerial(3,40);

SoftwareSerial serial(14,15);
RoboClaw roboclaw(&serial, 10000);
#define address 0x80

int HeadDirection = 0;
int RightSholderDirection = 0;
int RightElbowDirection = 0;
int LeftSholderDirection = 0;
int LeftElbowDirection = 0;
int NeckDirection = 0;
int DrivingDirection = 5;

USB Usb;
BTD Btd(&Usb);
PS3BT PS3(&Btd);

void exitSafeStart()
{
  HeadSerial.write(0x83);
  RightSholderSerial.write(0x83);
  RightElbowSerial.write(0x83);
  LeftSholderSerial.write(0x83);
  LeftElbowSerial.write(0x83);
  NeckSerial.write(0x83);
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

void Neck(int speed){
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

void Driving(int speed){
  if (speed == 0){
    roboclaw.BackwardM1(address,64);
    roboclaw.BackwardM2(address,64);
  }
  else if(speed == 1){
    roboclaw.ForwardM1(address,64);
    roboclaw.ForwardM2(address,64);
  }
  else{
    //nothing
  }
}
void setup()
{

  Serial.begin(9600);
  roboclaw.begin(38400);  

   if (Usb.Init() == -1) 
   {
    Serial.print("OSC did not start");
    Serial.println();
    while (1); //halt
   }

  Serial.print("PS3 Bluetooth Library Started");
  Serial.println();

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
  Usb.Task();

  /*-----------------------------------------*/
  if(PS3.getButtonPress(CROSS)){
    RightElbowDirection = -3200;
  }  
  else if(PS3.getButtonPress(TRIANGLE)){
    RightElbowDirection = 3200;
  }
  else{
    RightElbowDirection = -3200;(0);
  }
  /*-----------------------------------------*/
  if(PS3.getButtonPress(R1)){
    RightSholderDirection = 3200;
  } 
  else if(PS3.getButtonPress(R2)){
    RightSholderDirection = -3200;
  }
  else{
    RightSholderDirection = 0;
  }
/*-----------------------------------------*/
  if(PS3.getButtonPress(L1)){
    LeftSholderDirection = 3200;
  }  
  else if(PS3.getButtonPress(L2)){
    LeftSholderDirection = -3200;
  }
  else{
    LeftSholderDirection = 0;
  }
/*-----------------------------------------*/
  if(PS3.getButtonPress(UP)){
    LeftElbowDirection = 3200;
  } 
  else if(PS3.getButtonPress(DOWN)){
    LeftElbowDirection = -3200;
  }
  else{
    LeftElbowDirection = 0;
  }
/*-----------------------------------------*/
  if(PS3.getAnalogHat(RightHatX)< 125){
    HeadDirection = 3200;
  }
  else if(PS3.getAnalogHat(RightHatX) > 130){
    HeadDirection = -3200;
  }
  else{
    HeadDirection = 0;
  }
/*-----------------------------------------*/
  if(PS3.getAnalogHat(RightHatY)< 125){
    NeckDirection = 3200;
  }
  else if(PS3.getAnalogHat(RightHatY) > 130){
    NeckDirection = -3200;
  }
  else{
    NeckDirection = 0;
  }
/*-----------------------------------------*/

  if(PS3.getAnalogHat(LeftHatY) < 120){
    DrivingDirection = 1; //Forward
  }
  else if(PS3.getAnalogHat(LeftHatY) > 135){
    DrivingDirection = 0; //Backward
  }
  else{
    DrivingDirection = 3;
  }
  Head(HeadDirection);
  LeftSholder(LeftSholderDirection);
  LeftElbow(LeftElbowDirection);
  RightSholder(RightSholderDirection);
  RightElbow(RightElbowDirection);
  Neck(NeckDirection);
  Driving(DrivingDirection);
}

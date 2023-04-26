#include <SoftwareSerial.h>
#include <SPI.h>
#include <PS3BT.h>                                                    //Include the necessary libraries.
#include <Servo.h>
#include <SoftwareSerial.h>
#include "RoboClaw.h"

SoftwareSerial serial(3, 4);
RoboClaw roboclaw(&serial, 10000);
#define address 0x80

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
  roboclaw.begin(38400);
}

void loop(){
    for(int i=0; i<=8; i++){
        Driving(i);
        Serial.println(i);
        delay(2000);
    }
}

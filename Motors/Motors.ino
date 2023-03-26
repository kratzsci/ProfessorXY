#include <SoftwareSerial.h>
#include "RoboClaw.h"

SoftwareSerial serial(51,50);
RoboClaw roboclaw(&serial, 10000);

#define address 0x80

void setup() {
  // put your setup code here, to run once:
  roboclaw.begin(38400);

}

void loop() {
  // put your main code here, to run repeatedly:

  roboclaw.ForwardM1(address, 64);
  roboclaw.BackwardM2(address, 64);
  delay(2000);
  
  roboclaw.BackwardM1(address, 64);
  roboclaw.ForwardM2(address, 64);
  delay(2000);
}

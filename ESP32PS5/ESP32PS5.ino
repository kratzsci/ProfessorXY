#include <ps5Controller.h>

void onConnect() {
  Serial.println("Connected.");
}

void actions() {
  char transmit = 'P';

  // Share button
  if (ps5.Share()) {
    Serial.println("\nShare Button");
    transmit = 'A';
  }
  // Options button
  else if (ps5.Options()) {
    Serial.println("\nOptions Button");
    transmit = 'B';
  }
  // PS button
  else if (ps5.PSButton()) {
    Serial.println("\nPS Button");
    transmit = 'Z';
  }

  // Shape buttons
  else if (ps5.Square()) {
    Serial.println("\nSquare Button");
    transmit = 'S';
  }
  else if (ps5.Cross()) {
    Serial.println("\nCross Button");
    transmit = 'X';
  }
  else if (ps5.Circle()) {
    Serial.println("\nCircle Button");
    transmit = 'C';
  }
  else if (ps5.Triangle()) {
    Serial.println("\nTriangle Button");
    transmit = 'T';
  }

  // Directional buttons
  else if (ps5.Right()) {
    Serial.println("\nRight Button");
    transmit = 'R';
  }
  else if (ps5.Down()) {
    Serial.println("\nDown Button");
    transmit = 'D';
  }
  else if (ps5.Up()) {
    Serial.println("\nUp Button");
    transmit = 'U';
  }
  else if (ps5.Left()) {
    Serial.println("\nLeft Button");
    transmit = 'L';
  }

  // Bumpers
  else if (ps5.L1()) {
    Serial.println("\nL1 : Left Button");
    transmit = 'E';
  }
  else if (ps5.R1()) {
    Serial.println("\nR1 : Right Button");
    transmit = 'G';
  }

  // Triggers
  else if (ps5.L2()) {
    Serial.println("\nL2 : Left Trigger");
    transmit = 'F';
  }
  else if (ps5.R2()) {
    Serial.println("\nR2 : Right Trigger");
    transmit = 'H';
  }

  // Analog sticks
  else if (ps5.LStickX() > 64 && ps5.LStickY() > -64 && ps5.LStickY() < 64){
    Serial.println("\nTurn Right");
  
  }
  else if (ps5.LStickX() < -64 && ps5.LStickY() > -64 && ps5.LStickY() < 64){
    Serial.println("\nTurn Left");
  
  }
  else if (ps5.LStickY() > 64 && ps5.LStickX() > -64 && ps5.LStickX() < 64){
    Serial.println("\nForward");
  
  }
  else if (ps5.LStickY() < -64 && ps5.LStickX() > -64 && ps5.LStickX() < 64){
    Serial.println("\nBackward");
  
  }
  else{
    Serial.println("\nStop");
    
  }

  if(transmit != 'P'){
    Serial.write(transmit);
  }
  delay(100);
}


void setup() {
  Serial.begin(9600, SERIAL_8N1, 16, 17);
  delay(100);
//  ps5.attach(actions);
  ps5.attachOnConnect(onConnect);
  ps5.begin("a0:ab:51:bc:b8:ea"); //Current MAC address of controller

  Serial.println("Ready.");
  Serial.begin(9600);
}

void loop() {
  actions();
}

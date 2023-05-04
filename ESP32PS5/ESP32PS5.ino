#include <ps5Controller.h>
bool PS5Connected = false;
void onConnect() {
  Serial.println("Connected.");
  PS5Connected = true;
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
  // Touch Pad button
  else if (ps5.Touchpad()) {
    Serial.println("\nTouch Pad");
    transmit = 'Y'
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
    Serial.println("\nL1 : Left Bumper");
    transmit = 'E';
  }
  else if (ps5.R1()) {
    Serial.println("\nR1 : Right Bumper");
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

  // Left Analog sticks
  else if (ps5.LStickY() > 64 && ps5.LStickX() > -90 && ps5.LStickX() < 90){
    Serial.println("\nForward");
    transmit = '1';
  }
  else if (ps5.LStickY() < -64 && ps5.LStickX() > -90 && ps5.LStickX() < 90){
    Serial.println("\nBackward");
    transmit = '2';
  }
  else if (ps5.LStickX() > 64 && ps5.LStickY() => -90 && ps5.LStickY() =< 90){
    Serial.println("\nTurn Right");
    transmit = '3';
  }
  else if (ps5.LStickX() < -64 && ps5.LStickY() => -90 && ps5.LStickY() =< 90){
    Serial.println("\nTurn Left");
    transmit = '4';
  }

  // Right Analog sticks
  else if (ps5.RStickY() > 64 && ps5.RStickX() > -90 && ps5.RStickX() < 90){
    Serial.println("\nHead Up");
    transmit = '5';
  }
  else if (ps5.RStickY() < -64 && ps5.RStickX() > -90 && ps5.RStickX() < 90){
    Serial.println("\nHead Down");
    transmit = '6';
  }
  else if (ps5.RStickX() < -64 && ps5.RStickY() => -90 && ps5.RStickY() =< 90){
    Serial.println("\nNeck Left");
    transmit = '7';
  }
  else if (ps5.RStickX() > 64 && ps5.RStickY() => -90 && ps5.RStickY() =< 90){
    Serial.println("\nNeck Right");
    transmit = '8';
  }

  // Stop moving the robot when left analog stick is in center region
  else if (ps5.LStickX() =< -64 && ps5.LStickX() =< 64 && ps5.LStickY() =< -64 && ps5.LStickY() =< 64){
    Serial.println("\nStop moving robot");
    transmit = '0';
  }

  // If no buttons pressed Full stop
  else{
    if(PS5Connected == true){
      Serial.println("\nFull Stop");
      transmit = '9';
    }
  }
  // Ensure no null character
  if(transmit != 'P'){
    Serial.print("Transmit: ");
    Serial.println(transmit);
    Serial.write(transmit);
  }
  delay(100);
}


void setup() {
  Serial.begin(9600, SERIAL_8N1, 16, 17);
  delay(100);
  ps5.attachOnConnect(onConnect);
  ps5.begin("a0:ab:51:bc:b8:ea"); //Current MAC address of controller

  Serial.println("Ready.");
  Serial.begin(9600);
}

void loop() {
  actions();
}

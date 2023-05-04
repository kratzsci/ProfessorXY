<<<<<<< HEAD
#include <Ps3Controller.h>

void onConnect() {
  Serial.println("Connected.");
}

int filterJoystick(int rawValue) {
    const int BUFFER_SIZE = 10;
    static int buffer[BUFFER_SIZE]; // static buffer to keep track of past values
    static int index = 0;           // current index in the buffer
    int sum = 0;

    // Add the new raw value to the buffer and update the index
    buffer[index] = rawValue;
    index = (index + 1) % BUFFER_SIZE;

    // Sum of all values in the buffer
    for (int i = 0; i < BUFFER_SIZE; i++) {
        sum += buffer[i];
    }

    // Calculate and return the average value
    int average = sum / BUFFER_SIZE;
    return average;
}

void actions() {
  char transmit = 'P';
  int maxThrehold = 40;
  int minThreshold = 10;

  // Start button, upon press of the button
  // alt Ps3.data.button.start 
//  if( Ps3.event.button_down.start){
  if( Ps3.data.button.start){
    transmit = 'A';
  }
  // Select button, upon press of the button
  // alt Ps3.data.button.select
//  if( Ps3.event.button_down.select){
  if( Ps3.data.button.select){
    transmit = 'B';
  }
  // PS button, upon press of the button
  // alt Ps3.data.button.ps
//  if( Ps3.event.button_down.ps){
  if( Ps3.data.button.ps){
    transmit = 'Z';
  }

  // Shape buttons
  if (abs(Ps3.event.analog_changed.button.triangle)) {
    transmit = 'T';
  }
  if (abs(Ps3.event.analog_changed.button.cross)) {
    transmit = 'X';
  }
  if (abs(Ps3.event.analog_changed.button.square)) {
    transmit = 'S';
  }
  if (abs(Ps3.event.analog_changed.button.circle)) {
    transmit = 'C';
  }

  // Directional buttons
  if (abs(Ps3.event.analog_changed.button.left)) {
    transmit = 'L';
  }
  if (abs(Ps3.event.analog_changed.button.right)) {
    transmit = 'R';
  }
  if (abs(Ps3.event.analog_changed.button.up)) {
    transmit = 'U';
  }
  if (abs(Ps3.event.analog_changed.button.down)) {
    transmit = 'D';
  }

  // // Bumper left
  // if (abs(Ps3.event.analog_changed.button.l1)) {
  //   transmit = 'E';
  // }
  // // Trigger left
  // if (abs(Ps3.event.analog_changed.button.l2)) {
  //   transmit = 'F';
  // }

  // // Bumper right
  // if (abs(Ps3.event.analog_changed.button.r1)) {
  //   transmit = 'G';
  // }
  // // Trigger right 
  // if (abs(Ps3.event.analog_changed.button.r2)) {
  //   transmit = 'H';
  // }

  // Right analog stick, ry = y-axis, rx = x-axis
  // Left analog stick, ly = y-axis, lx = x-axis
  // if ( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ) {
  //   // Declare and read x and y axis
  //   int leftAxis = filterJoystick(Ps3.data.analog.stick.ly);
  //   int rightAxis = filterJoystick(Ps3.data.analog.stick.lx);

  //   if (leftAxis > maxThrehold && rightAxis < -maxThrehold) {
  //     //Backward Right
  //     transmit = '8';
  //   }
  //   else if (leftAxis > maxThrehold && rightAxis > maxThrehold) {
  //     //Backward Left
  //     transmit = '7';
  //   }
  //   else if (leftAxis < -maxThrehold && rightAxis < -maxThrehold) {
  //     //Forward Right
  //     transmit = '6';
  //   }
  //   else if (leftAxis < -maxThrehold && rightAxis > maxThrehold) {
  //     //Forward Left
  //     transmit = '5';
  //   }
  //   else if (rightAxis > minThreshold){
  //       //Left
  //       transmit = '4';
  //   }
  //   else if (rightAxis < -minThreshold){
  //       //Right
  //       transmit = '3';
  //   }
  //   else if (leftAxis > minThreshold){
  //       //Backward
  //       transmit = '2';
  //   }
  //   else if (leftAxis < -minThreshold){
  //       //Forward
  //       transmit = '1';
  //   }
  // }
  if(transmit != 'P'){
    Serial.write(transmit);
  }
}


void setup()
{
 Serial.begin(9600, SERIAL_8N1, 16, 17);
 delay(100);
 Ps3.attach(actions);
 // Serial.println("SerialRxd is on pin: " + String(RX));
 Ps3.attachOnConnect(onConnect);
 Ps3.begin("e8:48:b8:c8:20:00");   // Mac address of PS controller

 Serial.println("Ready.");
 Ps3.setPlayer(1);
}


void loop()
{

}
=======
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
    //Serial.println("\nShare Button");
    transmit = 'A';
  }
  // Options button
  else if (ps5.Options()) {
    //Serial.println("\nOptions Button");
    transmit = 'B';
  }
  // PS button
  else if (ps5.PSButton()) {
    //Serial.println("\nPS Button");
    transmit = 'Z';
  }

  // Shape buttons
  else if (ps5.Square()) {
    //Serial.println("\nSquare Button");
    transmit = 'S';
  }
  else if (ps5.Cross()) {
    //Serial.println("\nCross Button");
    transmit = 'X';
  }
  else if (ps5.Circle()) {
    //Serial.println("\nCircle Button");
    transmit = 'C';
  }
  else if (ps5.Triangle()) {
    //Serial.println("\nTriangle Button");
    transmit = 'T';
  }

  // Directional buttons
  else if (ps5.Right()) {
    //Serial.println("\nRight Button");
    transmit = 'R';
  }
  else if (ps5.Down()) {
    //Serial.println("\nDown Button");
    transmit = 'D';
  }
  else if (ps5.Up()) {
    //Serial.println("\nUp Button");
    transmit = 'U';
  }
  else if (ps5.Left()) {
    //Serial.println("\nLeft Button");
    transmit = 'L';
  }

  // Bumpers
  else if (ps5.L1()) {
    //Serial.println("\nL1 : Left Button");
    transmit = 'E';
  }
  else if (ps5.R1()) {
    //Serial.println("\nR1 : Right Button");
    transmit = 'G';
  }

  // Triggers
  else if (ps5.L2()) {
    //Serial.println("\nL2 : Left Trigger");
    transmit = 'F';
  }
  else if (ps5.R2()) {
    //Serial.println("\nR2 : Right Trigger");
    transmit = 'H';
  }

  // Analog sticks
  else if (ps5.LStickX() > 64 && ps5.LStickY() > -90 && ps5.LStickY() < 90){
    //Serial.println("\nTurn Right");
    transmit = '3';
  }
  else if (ps5.LStickX() < -64 && ps5.LStickY() > -90 && ps5.LStickY() < 90){
    //Serial.println("\nTurn Left");
    transmit = '4';
  }
  else if (ps5.LStickY() > 64 && ps5.LStickX() > -90 && ps5.LStickX() < 90){
    //Serial.println("\nForward");
    transmit = '1';
  }
  else if (ps5.LStickY() < -64 && ps5.LStickX() > -90 && ps5.LStickX() < 90){
    //Serial.println("\nBackward");
    transmit = '2';
  }
  else{
    //Serial.println("\nStop");
    if(PS5Connected == true){
      transmit = '0';
    }
  }

  if(transmit != 'P'){
//    //Serial.print("Transmit: ");
//    //Serial.println(transmit);
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

  //Serial.println("Ready.");
  Serial.begin(9600);
}

void loop() {
  actions();
}
>>>>>>> origin/main

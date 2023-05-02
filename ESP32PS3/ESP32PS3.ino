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

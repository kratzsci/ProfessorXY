#include <Ps3Controller.h>

void onConnect() {
  Serial.println("Connected.");
}

char transmit = 'P';

void actions() {
  if ( abs(Ps3.event.analog_changed.button.triangle) ) {
    transmit = 'T';
  }
  else if ( abs(Ps3.event.analog_changed.button.cross) ) {
    transmit = 'X';
  }
  else if ( abs(Ps3.event.analog_changed.button.left) ) {
    transmit = 'L';
  }
  else if ( abs(Ps3.event.analog_changed.button.right) ) {
    transmit = 'R';
  }
  else if ( abs(Ps3.event.analog_changed.button.square) ) {
    transmit = 'S';
  }
  else if ( abs(Ps3.event.analog_changed.button.circle) ) {
    transmit = 'C';
  }
  else if ( abs(Ps3.event.analog_changed.button.up) ) {
    transmit = 'U';
  }
  else if ( abs(Ps3.event.analog_changed.button.down) ) {
    transmit = 'D';
  }
  else if ( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ) {
    if (Ps3.data.analog.stick.ly > 40 && Ps3.data.analog.stick.lx <-40) {
      //Backward Right
      transmit = '8';
    }
    else if (Ps3.data.analog.stick.ly > 40 && Ps3.data.analog.stick.lx > 40) {
      //Backward Left
      transmit = '7';
    }
    else if (Ps3.data.analog.stick.ly < -40 && Ps3.data.analog.stick.lx <-40) {
      //Forward Right
      transmit = '6';
    }
    else if (Ps3.data.analog.stick.ly < -40 && Ps3.data.analog.stick.lx >40) {
      //Forward Left
      transmit = '5';
    }
    else if (Ps3.data.analog.stick.lx > 10){
        //Left
        transmit = '4';
    }
    else if (Ps3.data.analog.stick.lx < -10){
        //Right
        transmit = '3';
    }
    else if (Ps3.data.analog.stick.ly > 10){
        //Backward
        transmit = '2';
    }
    else if (Ps3.data.analog.stick.ly < -10){
        //Forward
        transmit = '1';
    }
    else{
      transmit = 'P';
    }
  }
  else {
    transmit = 'P';
  }
  if(transmit != 'P'){
    Serial.write(transmit);
  }
}


void setup()
{
  Serial.begin(9600, SERIAL_8N1, 16, 17);
  delay(100);
  Ps3.attach(actions);
  Serial.println("SerialRxd is on pin: " + String(RX));
  Ps3.attachOnConnect(onConnect);
  Ps3.begin("e8:48:b8:c8:20:00");
  Serial.println("Ready.");
  Ps3.setPlayer(1);
}



void loop()
{

}
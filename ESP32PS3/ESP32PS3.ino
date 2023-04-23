#include <Ps3Controller.h>

void onConnect(){
    Serial.println("Connected.");
}

void actions(){
    if( abs(Ps3.event.analog_changed.button.triangle) ){
       Serial.write("T");
   }
   if( abs(Ps3.event.analog_changed.button.square) ){
       Serial.write("S");
   }
   if( abs(Ps3.event.analog_changed.button.circle) ){
       Serial.write("C");
   }
   if( abs(Ps3.event.analog_changed.button.cross) ){
       Serial.write("X");
   }
}


void setup()
{
    Serial.begin(9600, SERIAL_8N1, 16, 17);
    delay(100);
    Ps3.attach(actions);
    Serial.println("SerialRxd is on pin: "+String(RX));
    Ps3.attachOnConnect(onConnect);
    Ps3.begin("e8:48:b8:c8:20:00");
    Serial.println("Ready.");
    Ps3.setPlayer(1);
}



void loop()
{

}

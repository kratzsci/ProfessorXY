#include <SoftwareSerial.h>
char received;

void setup(){
  Serial.begin(9600);
  delay(100);
}

// Arduino Uno code to receive the message
void loop(){
  if(Serial.available()>0){
    
    received = Serial.read();
    Serial.print(received);
  }
}
